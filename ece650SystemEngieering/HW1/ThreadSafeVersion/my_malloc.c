#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<sys/time.h>
#include<stdint.h>
#include<pthread.h>
#include"my_malloc.h"

#define WSIZE 4
#define DSIZE 8
#define MINSIZE 16
#define CHUNKSIZE (1<<7)
#define PADDING(size) (((size+WSIZE)%16==0)? (size+WSIZE):(((size+WSIZE)/16+1)*16))

#define MAX(x,y) (((x)>(y))? (x):(y))
#define GET(addr) (*(size_t *)(addr))
#define PUT(addr, value) (*((size_t *)(addr))=(size_t)(value))
#define GET_SIZE(addr) (GET(addr) & (~0x7))
#define GET_ALLOC(addr) (GET(addr) & 0x1)
#define PACK(size,alloc) ((size)|(alloc))

#define HA(addr) ((char *)(addr)-WSIZE) //get head block address
#define FA(addr) ((char *)(addr)+GET_SIZE(HA(addr))-DSIZE)//get foot block address
#define FLN(addr) ((char *)(addr))
#define FLP(addr) ((char *)(addr)+WSIZE)

#define PRE_BLOCK(addr) (addr-GET_SIZE(addr-DSIZE))
#define NEXT_BLOCK(addr) (FA(addr)+DSIZE)
#define NFA(addr) ((char *)GET(FLN(addr)))
#define PFA(addr) ((char *)GET(FLP(addr)))
#define FFA ((char *)GET(list_start))
#define EFA ((char *)GET(FLP(list_end)))

char *heap_start=NULL;
char *list_start=NULL;
char *list_end=NULL;
char *heap_end=NULL;
int heap_size=0;
int used_size=0;
int flag=0;
int flag1=0;
int times=0;

pthread_rwlock_t general_lock = PTHREAD_RWLOCK_INITIALIZER; 
pthread_mutex_t ini_lock = PTHREAD_MUTEX_INITIALIZER; 


int m_init();
void *m_expand(size_t size);
void ts_free(void *addr);
void *ts_malloc(size_t size);
void *m_coalesce_next(char *addr);
void *m_coalesce_pre(char *addr);
void *m_add_fl(char *addr);
void *m_split(char *addr, size_t size);


unsigned long get_data_segment_size(){
  return (unsigned long)heap_size;
}


unsigned long get_data_segment_free_space_size(){
  return (unsigned long)(heap_size-used_size);
}

int m_init(){
  if((heap_start=(char *)sbrk(84))==(char *)-1){
    printf("The initialization fail\n");
    return -1;
  }
  list_start=heap_start+WSIZE;
  heap_end=(char *)sbrk(0);
  list_end=heap_end-DSIZE;
  heap_size=(int)(heap_end-heap_start);
  used_size=2*DSIZE+WSIZE;
  PUT(heap_start, PACK(8,1));//the first head
  PUT(list_start, (size_t )((char *)list_start+8));//the freelist head point to first free space
  
  PUT(HA(list_end),PACK(8,1));
  PUT(FLP(list_end),FFA);
  PUT(HA(FFA),PACK(64,0));// the first free space head
  PUT(FA(FFA),PACK(64,0));// the first free space foot
  PUT(FLN(FFA),list_end);// the first free space next pointer
  PUT(FLP(FFA),list_start);// the first free space previous pointer
  return 0;
}

void *m_expand(size_t size){
  if( ((char *)sbrk(MAX(size,CHUNKSIZE)))==(char *)-1 ){
    printf("The expand fail\n");
    abort();
  }
  char *old_heap_end=heap_end;
  char *old_list_end=list_end;
  char *pre_end=(char *)PFA(list_end);
  heap_size+=MAX(size,CHUNKSIZE);
  heap_end=(char *)sbrk(0);
  list_end=heap_end-DSIZE;
  PUT(HA(list_end),PACK(8,1));
  PUT(FLP(list_end),pre_end);
  PUT(FLN(pre_end),list_end);
  PUT(HA(old_list_end),PACK(MAX(size,CHUNKSIZE),0));
  PUT(FA(old_list_end),PACK(MAX(size,CHUNKSIZE),0));
  char *new_block=(char *)m_coalesce_pre(m_add_fl(old_list_end));
  return m_split(new_block,size);
}

void ts_free(void *addr){
  PUT(HA(addr),PACK(GET_SIZE(HA(addr)),0));
  PUT(FA(addr),PACK(GET_SIZE(FA(addr)),0));
  used_size-=GET_SIZE(HA(addr));
  pthread_rwlock_wrlock(&general_lock);
  m_coalesce_next(m_coalesce_pre(m_add_fl((char *)addr)));
  pthread_rwlock_unlock(&general_lock);
}

void *ts_malloc(size_t size){
  if(flag1==0){
    pthread_mutex_lock(&ini_lock);
    if(flag==0){
      m_init();
      flag = 1;
      flag1 = 1;
    }
    pthread_mutex_unlock(&ini_lock);
  }
    
  size=PADDING(size);
  pthread_rwlock_rdlock(&general_lock);//
  char *current = FFA;
  char *best_fit = FFA;
  int index = 0;
  if( (size_t)GET_SIZE(HA(best_fit))>=size )
    index = 1;
  while(current!=list_end){
    if( ((size_t)GET_SIZE(HA(current))>=size) && ((size_t)GET_SIZE(HA(current))<=(size_t)GET_SIZE(HA(best_fit))) ){
      best_fit = current;
      index=1;
      if((size_t)GET_SIZE(HA(best_fit))==size)
        break;
    }
    current = (char *)NFA(current);
  }
  if(index==0){
    pthread_rwlock_unlock(&general_lock);
    pthread_rwlock_wrlock(&general_lock);
    char * new_block = m_expand(size);
    pthread_rwlock_unlock(&general_lock);
    return new_block;
  }
  else{
    pthread_rwlock_unlock(&general_lock);
    pthread_rwlock_wrlock(&general_lock);
    if((best_fit=m_split(best_fit,size))!=NULL){
      pthread_rwlock_unlock(&general_lock);
      return best_fit;
    }
    else{
      char *new_block = m_expand(size);
      pthread_rwlock_unlock(&general_lock);
      return new_block;
    }
  }
}
  


void *m_coalesce_next(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  if( (GET_ALLOC(HA(NEXT_BLOCK(addr)))==0)&&(addr!=(char *)EFA) ){
    char * next_addr = NEXT_BLOCK(addr);
    size_t new_size = GET_SIZE(HA(addr)) + GET_SIZE(HA(NEXT_BLOCK(addr)));
    char * pre_fl = (char *)PFA(next_addr);
    char * next_fl = (char *)NFA(next_addr);
    PUT(FLN(pre_fl),next_fl);
    PUT(FLP(next_fl),pre_fl);
    PUT(HA(addr),PACK(new_size,0));
    PUT(FA(addr),PACK(new_size,0));
  }
  return addr;
}


void *m_coalesce_pre(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  if( (GET_ALLOC(addr-DSIZE)==0)&&(PRE_BLOCK(addr)<heap_end)&&(PRE_BLOCK(addr)>heap_start)&&(GET_ALLOC(HA(PRE_BLOCK(addr)))==0)&&(GET_SIZE(HA(PRE_BLOCK(addr)))==GET_SIZE(addr-DSIZE))&&(addr!=(char *)FFA) ){
    char *pre_addr = PRE_BLOCK(addr);
    size_t new_size = GET_SIZE(HA(addr)) + GET_SIZE(HA(PRE_BLOCK(addr)));
    char * pre_fl = (char *)PFA(addr);
    char * next_fl = (char *)NFA(addr);
    PUT(FLN(pre_fl),next_fl);
    PUT(FLP(next_fl),pre_fl);
    PUT(HA(pre_addr),PACK(new_size,0));
    PUT(FA(pre_addr),PACK(new_size,0));
    return pre_addr;
  }
  else
    return addr;
}
  
void *m_add_fl(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  char * old_ffa = (char *)FFA;
  PUT(FLP(old_ffa),addr);
  PUT(FLN(addr),old_ffa);
  PUT(FLN(list_start),addr);
  PUT(FLP(addr),list_start);
  return addr;
}

void *m_split(char *addr, size_t size){
  assert(size%16==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  if(GET_SIZE(HA(addr))<size){
    //printf("The block you find for split is too small  !");
    return NULL;
  }
  else if((GET_SIZE(HA(addr)))==size){ 
    PUT(HA(addr),PACK(size,1));
    PUT(FA(addr),PACK(size,1));
    used_size+=size;
    char *next_fl=(char *)NFA(addr);
    char *pre_fl=(char *)PFA(addr);
    PUT(FLN(pre_fl),next_fl);
    PUT(FLP(next_fl),pre_fl);
    return addr;
  } 
  else{
    size_t new_size=GET_SIZE(HA(addr))-size;
    PUT(HA(addr),PACK(size,1));
    PUT(FA(addr),PACK(size,1));
    used_size+=size;
    char *next_fl=(char *)NFA(addr);
    char *pre_fl=(char *)PFA(addr);
    char *rest_addr=NEXT_BLOCK(addr);
    PUT(FLN(pre_fl),rest_addr);
    PUT(FLP(rest_addr),pre_fl);
    PUT(FLP(next_fl),rest_addr);
    PUT(FLN(rest_addr),next_fl);
    PUT(HA(rest_addr),PACK(new_size,0));
    PUT(FA(rest_addr),PACK(new_size,0));
    return addr;
  }
}

