#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <time.h>
#include "potato.h"

int main(int argc, char *argv[])
{
  if(argc != 3){
    printf("Wrong number of argv for ringmaster!\n");
    return EXIT_FAILURE;
  }
  int n_p = atoi(argv[1]);
  int n_h = atoi(argv[2]);
  if(n_p <= 0){
    printf("The number of player is less than 0\n");
    return EXIT_FAILURE;
  }

    
  if( (n_h < 0)||(n_h>512)||(n_p<=1 ) ){
    printf("The number of hops is negative or larger than 512 or number of player less than 1\n");
    master_fifo* MasterFifo=master_fifo_initial(n_p,n_h);
    int n=-1;
    for(int i=0;i<n_p;i++){
      MasterFifo[i].master_to_fd=open(MasterFifo[i].master_to,O_RDONLY);
      MasterFifo[i].master_from_fd=open(MasterFifo[i].master_from,O_WRONLY);
      assert(write(MasterFifo[i].master_from_fd,&n,sizeof(n_p))!=-1);
    } 
    
    
    for(int i=0;i<n_p;i++){
      close(MasterFifo[i].master_to_fd);
      close(MasterFifo[i].master_from_fd);
    }
    master_fifo_free(MasterFifo,n_p);
    return EXIT_FAILURE;
  }
  
  printf("Potato Ringmaster\n");
  printf("Players = %d\n",n_p);
  printf("Hops = %d\n",n_h);
  

  char* in_message = malloc(BUFF_LEN*sizeof(*in_message));
  master_fifo* MasterFifo=master_fifo_initial(n_p,n_h);
  fd_set rset;

  for(int i=0;i<n_p;i++){
    MasterFifo[i].master_to_fd=open(MasterFifo[i].master_to,O_RDONLY);
    MasterFifo[i].master_from_fd=open(MasterFifo[i].master_from,O_WRONLY);
    assert(write(MasterFifo[i].master_from_fd,&n_p,sizeof(n_p))!=-1);
  } 
  
  
  for(int i=0;i<n_p;i++){
    clear_string(in_message);
    assert(read(MasterFifo[i].master_to_fd,in_message,BUFF_LEN)!=-1);
    printf("%s\n",in_message);
  }
  
  POTATO_T item;
  memset(&item,0,sizeof(item));

  POTATO_T item_r;
  memset(&item_r,0,sizeof(item_r));

  if(n_h!=0){
    srand((unsigned)time(NULL));
    int id=rand()%n_p;
    printf("All players present, sending potato to player %d\n",id);
    item.hop_count=item.total_hops=n_h;

    assert(write(MasterFifo[id].master_from_fd,&item,sizeof(item))!=-1);



    int nfds=MasterFifo[0].master_to_fd;
    FD_ZERO(&rset);
    for(int i=0;i<n_p;i++){
      FD_SET(MasterFifo[i].master_to_fd,&rset);
      nfds=(MasterFifo[i].master_to_fd>nfds)?MasterFifo[i].master_to_fd:nfds;
    }
    assert(select(nfds+1,&rset,NULL,NULL,NULL)>0);

    for(int i=0;i<n_p;i++){
      if(FD_ISSET(MasterFifo[i].master_to_fd,&rset)){
        printf("Trace of potato:\n");
        assert(read(MasterFifo[i].master_to_fd,&item_r,sizeof(item_r))!=-1);
      
        break;
      }
    }
  }
  POTATO_T end;
  memset(&end,0,sizeof(end));
  end.hop_count=1;
  end.total_hops=-1;

  for(int i=0;i<n_p;i++){  
    assert(write(MasterFifo[i].master_from_fd,&end,sizeof(end))!=-1); 
  }
 

  for(int i=0;i<n_p;i++){
    clear_string(in_message);
    assert(read(MasterFifo[i].master_to_fd,in_message,BUFF_LEN)!=-1);
  }
  
  if(n_h!=0){
    for(int j=0;j<item_r.total_hops-1;j++){
      printf("%lu,",item_r.hop_trace[j]);
    }
    printf("%lu\n",item_r.hop_trace[item_r.total_hops-1]);
  }



  
  for(int i=0;i<n_p;i++){
    close(MasterFifo[i].master_to_fd);
    close(MasterFifo[i].master_from_fd);
  }
  master_fifo_free(MasterFifo,n_p);
  free(in_message);
  return EXIT_SUCCESS;
}

