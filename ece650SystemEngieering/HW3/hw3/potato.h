#define BUFF_LEN   512
#define MAX_POTATO 512
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct potato {
  char msg_type;

  int total_hops;
  int hop_count;

  unsigned long hop_trace[MAX_POTATO];
} POTATO_T;

void initial(POTATO_T* item){
  item->msg_type='a';
  item->total_hops=0;
  item->hop_count=0;
  for(int i=0;i<MAX_POTATO;i++)
    item->hop_trace[i]=0;
}
typedef struct _player_fifo{
  char* master_to;
  char* master_from;
  char* player_to;
  char* player_from;
  char* player_to_before;
  char* player_from_before;
  int master_to_fd;
  int master_from_fd;
  int player_to_fd;
  int player_from_fd;
  int player_to_before_fd;
  int player_from_before_fd;
}player_fifo;

typedef struct _master_fifo{
  char* master_to;
  char* master_from;
  int master_to_fd;
  int master_from_fd;
}master_fifo;

void clear_string( char *s ) {
  int i;
  for ( i=0; i < BUFF_LEN; i++ ) {
    s[i] = '\0';
  }
}

void player_fifo_free(player_fifo* PlayerFifo);
void player_pure_free(player_fifo* PlayerFifo);

void player_open(int id,int n_p,player_fifo* PlayerFifo){
   if(n_p>2){
    if(id==0){
      PlayerFifo->player_to_fd=open(PlayerFifo->player_to,O_WRONLY);
      PlayerFifo->player_from_fd=open(PlayerFifo->player_from,O_RDONLY);
      PlayerFifo->player_to_before_fd=open(PlayerFifo->player_to_before,O_WRONLY);
      PlayerFifo->player_from_before_fd=open(PlayerFifo->player_from_before,O_RDONLY);
    }
    else if(id<(n_p-1)){
      PlayerFifo->player_from_before_fd=open(PlayerFifo->player_from_before,O_RDONLY);
      PlayerFifo->player_to_before_fd=open(PlayerFifo->player_to_before,O_WRONLY);
      PlayerFifo->player_to_fd=open(PlayerFifo->player_to,O_WRONLY);
      PlayerFifo->player_from_fd=open(PlayerFifo->player_from,O_RDONLY);
    }
    else if(id==(n_p-1)){
      PlayerFifo->player_from_before_fd=open(PlayerFifo->player_from_before,O_RDONLY);
      PlayerFifo->player_to_before_fd=open(PlayerFifo->player_to_before,O_WRONLY);
      PlayerFifo->player_from_fd=open(PlayerFifo->player_from,O_RDONLY);
      PlayerFifo->player_to_fd=open(PlayerFifo->player_to,O_WRONLY);
    }

  }
  else{ 
    if(id==0){
      PlayerFifo->player_to_before_fd=PlayerFifo->player_to_fd=open(PlayerFifo->player_to,O_WRONLY);
      PlayerFifo->player_from_before_fd=PlayerFifo->player_from_fd=open(PlayerFifo->player_from,O_RDONLY);
    }
    else{
      PlayerFifo->player_from_before_fd=PlayerFifo->player_from_fd=open(PlayerFifo->player_from,O_RDONLY);
      PlayerFifo->player_to_before_fd=PlayerFifo->player_to_fd=open(PlayerFifo->player_to,O_WRONLY);
    }
  }

}


player_fifo* player_fifo_initial0(int index){
  player_fifo* result=malloc(sizeof(*result));
  
  result->master_to=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->master_to,"/tmp/p%d_master",index);

  result->master_from=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->master_from,"/tmp/master_p%d",index);

  return result;
}


void player_fifo_initial1(player_fifo* result,int index,int n_p){
  result->player_to=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->player_to,"/tmp/p%d_p%d",index,(index+1)%n_p);

  result->player_from=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->player_from,"/tmp/p%d_p%d",(index+1)%n_p,index);

  result->player_to_before=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->player_to_before,"/tmp/p%d_p%d",index,((index==0)?(n_p-1):((index-1)%n_p)) );
  
  result->player_from_before=malloc(BUFF_LEN*sizeof(char));
  sprintf(result->player_from_before,"/tmp/p%d_p%d",((index==0)?(n_p-1):((index-1)%n_p)),index);
}

master_fifo* master_fifo_initial(int n_p,int n_h){
  master_fifo* result=malloc(n_p*sizeof(*result));
  for(int i=0;i<n_p;i++){
    result[i].master_to=malloc(BUFF_LEN*sizeof(char));
    sprintf(result[i].master_to,"/tmp/p%d_master",i);
    result[i].master_from=malloc(BUFF_LEN*sizeof(char));
    sprintf(result[i].master_from,"/tmp/master_p%d",i);
    if( (mkfifo(result[i].master_from,0666)&&(errno!=EEXIST)) || (mkfifo(result[i].master_to,0666)&&(errno!=EEXIST)) ){
      printf("Can not create master to player fifo\n");
      exit(0);
    }
    if( (n_p>=2)&&(n_h>=0)&&(n_h<=512)){
      player_fifo* PlayerFifo=player_fifo_initial0(i);
      player_fifo_initial1(PlayerFifo,i,n_p);
    
      if( (mkfifo(PlayerFifo->player_to,0666)&&(errno!=EEXIST)) || (mkfifo(PlayerFifo->player_from,0666)&&(errno!=EEXIST)) ){
        printf("Can not create player to player fifo\n");
        exit(0);
      }
      player_pure_free(PlayerFifo);
    }
  }
  return result;
}

void master_fifo_free(master_fifo* MasterFifo,int n_p){
  for(int i=0;i<n_p;i++){
    unlink(MasterFifo[i].master_to);
    unlink(MasterFifo[i].master_from);
    free(MasterFifo[i].master_to);
    free(MasterFifo[i].master_from);
  }
  free(MasterFifo);
}

void player_fifo_free(player_fifo* PlayerFifo){
  free(PlayerFifo->master_to);
  free(PlayerFifo->master_from);
  unlink(PlayerFifo->player_to);
  free(PlayerFifo->player_to);
  unlink(PlayerFifo->player_from);
  free(PlayerFifo->player_from);
  free(PlayerFifo->player_to_before);
  free(PlayerFifo->player_from_before);
  free(PlayerFifo);
}


void player_pure_free(player_fifo* PlayerFifo){
  free(PlayerFifo->master_to);
  free(PlayerFifo->master_from);
  free(PlayerFifo->player_to);
  free(PlayerFifo->player_from);
  free(PlayerFifo->player_to_before);
  free(PlayerFifo->player_from_before);
  free(PlayerFifo);
}

void masterfifolist(master_fifo* MasterFifo){
  printf("ringmaster %s %d\n",MasterFifo->master_to,MasterFifo->master_to_fd);
  printf("ringmaster %s %d\n",MasterFifo->master_from,MasterFifo->master_from_fd);
}

void playerfifolist(player_fifo* PlayerFifo){
  printf("player %s %d\n",PlayerFifo->master_to,PlayerFifo->master_to_fd);
  printf("player %s %d\n",PlayerFifo->master_from,PlayerFifo->master_from_fd);
  printf("player %s %d\n",PlayerFifo->player_to,PlayerFifo->player_to_fd);
  printf("player %s %d\n",PlayerFifo->player_from,PlayerFifo->player_from_fd);
  printf("player %s %d\n",PlayerFifo->player_to_before,PlayerFifo->player_to_before_fd);
  printf("player %s %d\n",PlayerFifo->player_from_before,PlayerFifo->player_from_before_fd);
}
