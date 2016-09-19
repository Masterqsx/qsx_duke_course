#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <time.h>

#include "potato.h"

int main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Wring number of argv for player!\n");
    return EXIT_FAILURE;
  }
  int id = atoi(argv[1]);
  if(id < 0){
    printf("The id of player is negative\n");
    return EXIT_FAILURE;
  }
   

  player_fifo* PlayerFifo=player_fifo_initial0(id);
  
  PlayerFifo->master_to_fd=open(PlayerFifo->master_to,O_WRONLY);
  PlayerFifo->master_from_fd=open(PlayerFifo->master_from,O_RDONLY);

  int n_p=0;
  char* out_message=malloc(BUFF_LEN*sizeof(*out_message));
  
  fd_set rset;
  assert(read(PlayerFifo->master_from_fd,&n_p,sizeof(n_p))!=-1);

  if(n_p==-1){
    free(out_message);
    close(PlayerFifo->master_to_fd);
    close(PlayerFifo->master_from_fd);
    player_fifo_free(PlayerFifo);
    return EXIT_FAILURE;
  }

  printf("Connected as player %d out of %d total palyers\n",id,n_p);
  player_fifo_initial1(PlayerFifo,id,n_p);

  player_open(id,n_p,PlayerFifo); 

  
  
  clear_string(out_message);
  sprintf(out_message,"Player %d is ready to play",id);
  assert(write(PlayerFifo->master_to_fd,out_message,BUFF_LEN)!=-1);




  srand((unsigned)time(NULL)+id*10);
  unsigned int ran=rand()%2; 
  POTATO_T item;
  memset(&item,0,sizeof(item));
  while(1){
    FD_ZERO(&rset);
    FD_SET(PlayerFifo->player_from_before_fd,&rset);
    FD_SET(PlayerFifo->master_from_fd,&rset);
    FD_SET(PlayerFifo->player_from_fd,&rset);
    int nfds=(PlayerFifo->player_from_before_fd>PlayerFifo->master_from_fd)?PlayerFifo->player_from_before_fd:PlayerFifo->master_from_fd;
    nfds=((nfds>PlayerFifo->player_from_fd)?nfds:PlayerFifo->player_from_fd);
    assert(select(nfds+1,&rset,NULL,NULL,NULL)>0);

    if(FD_ISSET(PlayerFifo->master_from_fd,&rset)){
      assert(read(PlayerFifo->master_from_fd,&item,sizeof(item))!=-1);
      if(item.hop_count==1){
        if(item.total_hops==1){
          printf("I'm it\n");
          item.hop_trace[item.total_hops-item.hop_count]=id;
          assert(write(PlayerFifo->master_to_fd,&item,sizeof(item))!=-1);
          
        }
        else if(item.total_hops==-1)
          break;
      }
      else{
        item.hop_trace[item.total_hops-item.hop_count]=id;
        item.hop_count--;
        ran=rand()%2;
        if(ran==1){
          assert(write(PlayerFifo->player_to_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",(id+1)%n_p);
        }
        else if(ran==0){
          assert(write(PlayerFifo->player_to_before_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",((id==0)?(n_p-1):(id-1)%n_p) );
        }
      }
    }
    
    else if(FD_ISSET(PlayerFifo->player_from_before_fd,&rset)){
      assert(read(PlayerFifo->player_from_before_fd,&item,sizeof(item))!=-1);
      if(item.hop_count==1){
        printf("I'm it\n");
        item.hop_trace[item.total_hops-item.hop_count]=id;
        assert(write(PlayerFifo->master_to_fd,&item,sizeof(item))!=-1);
 
      }
      else{
        item.hop_trace[item.total_hops-item.hop_count]=id;
        item.hop_count--;
        ran=rand()%2;
        if(ran==1){
          assert(write(PlayerFifo->player_to_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",(id+1)%n_p);
        }
        else if(ran==0){
          assert(write(PlayerFifo->player_to_before_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",((id==0)?(n_p-1):(id-1)%n_p) );
        }
      }
    }
    
    else if(FD_ISSET(PlayerFifo->player_from_fd,&rset)){
      assert(read(PlayerFifo->player_from_fd,&item,sizeof(item))!=-1);
      if(item.hop_count==1){
        printf("I'm it\n");
        item.hop_trace[item.total_hops-item.hop_count]=id;
        assert(write(PlayerFifo->master_to_fd,&item,sizeof(item))!=-1);
 
      }
      else{
        item.hop_trace[item.total_hops-item.hop_count]=id;
        item.hop_count--;
        ran=rand()%2;
        if(ran==1){
          assert(write(PlayerFifo->player_to_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",(id+1)%n_p);
        }
        else if(ran==0){
          assert(write(PlayerFifo->player_to_before_fd,&item,sizeof(item))!=-1);
          printf("Sending potato to %d\n",((id==0)?(n_p-1):(id-1)%n_p) );
        }
      }
    }

  }
  
  clear_string(out_message);
  sprintf(out_message,"Player %d is ready to exit",id);
  assert(write(PlayerFifo->master_to_fd,out_message,BUFF_LEN)!=-1);
  sleep(1);

  free(out_message);
  close(PlayerFifo->master_to_fd);
  close(PlayerFifo->master_from_fd);
  close(PlayerFifo->player_to_fd);
  close(PlayerFifo->player_from_fd);
  close(PlayerFifo->player_to_before_fd);
  close(PlayerFifo->player_from_before_fd);
  
  player_fifo_free(PlayerFifo);
  return EXIT_SUCCESS;
}

