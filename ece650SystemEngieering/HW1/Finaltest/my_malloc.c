#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<sys/time.h>
#include<stdint.h>
#include<sys/resource.h>
#include<sys/types.h>
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
#define NFA(addr) GET(FLN(addr))
#define PFA(addr) GET(FLP(addr))
#define LS(index) (list_start+(index)*WSIZE)
#define LE(index) (list_end+(index)*WSIZE)
#define FFA(index) ((char *)GET(list_start+(index)*WSIZE))
#define EFA(index) ((char *)GET(FLP(list_end+(index)*WSIZE)))

char *heap_start=NULL;
char *list_start=NULL;
char *list_end=NULL;
char *heap_end=NULL;
int heap_size=0;
int used_size=0;
int flag=0;
int times=0;
struct rlimit r;

int m_init();
int m_fl_cal(size_t size);
void *m_expand(size_t size);
void ff_free(void *addr);
void bf_free(void *addr);
void wf_free(void *addr);
void m_free_noncoalesce(void *addr);
void *ff_malloc(size_t size);
void *bf_malloc(size_t size);
void *wf_malloc(size_t size);
void *m_coalesce_next(char *addr);
void *m_coalesce_pre(char *addr);
void *m_add_fl(char *addr);
void *m_split(char *addr, size_t size);
void display_free();
void display_all();

unsigned long get_data_segment_size(){
	return ((unsigned long)sbrk(0)-(unsigned long)heap_start);
}


unsigned long get_data_segment_free_space_size(){
	return (unsigned long)(heap_size-used_size);
}


int m_init(){
  if((heap_start=(char *)sbrk(17*WSIZE))==(char *)-1){
    printf("The initialization fail\n");
    return -1;
  }

  list_start=heap_start+WSIZE;
  heap_end=(char *)sbrk(0);
  list_end=heap_end-8*WSIZE;
  heap_size=(int)(heap_end-heap_start);
  used_size=8*WSIZE+9*WSIZE;
  PUT(heap_start, PACK(8,1));//the first head
  PUT(FLN(LS(0)),LE(0));//the freelist head point to first free space
  PUT(FLP(LE(0)),LS(0));
  
  PUT(FLN(LS(1)),LE(1));
  PUT(FLP(LE(1)),LS(1));
  
  PUT(FLN(LS(2)),LE(2));
  PUT(FLP(LE(2)),LS(2));
  
  PUT(FLN(LS(3)),LE(3));
  PUT(FLP(LE(3)),LS(3));
  
  PUT(FLN(LS(4)),LE(4));
  PUT(FLP(LE(4)),LS(4));
  
  PUT(FLN(LS(5)),LE(5));
  PUT(FLP(LE(5)),LS(5));
  
  PUT(FLN(LS(6)),LE(6));
  PUT(FLP(LE(6)),LS(6));
  
  PUT(HA(list_end),PACK(8,1));
  PUT(FLN(list_end),NULL);
  return 0;
}

int m_fl_cal(size_t size){
  if(size<=64){
    return 0;
  }
  if(size<=128){
    return 1;
  }
  if(size<=512){
    return 2;
  }
  if(size<=1024){
    return 3;
  }
  if(size<=4096){
    return 4;
  }
  if(size<=16384){
    return 5;
  }
	if(size>16384){
    return 6;
	}
	else{
		printf("Unknown size %zu\n",size);
		abort();
	}
}


void *m_expand(size_t size){
  times++;
	if( ((char *)sbrk(MAX(size,CHUNKSIZE)))==(char *)-1 ){
		printf("The expand fail,already expand %d\n",times);
    abort();
  }
  char *old_heap_end=heap_end;
  char *old_list_end=list_end;

  char *pre_end[7]={NULL};
  for(int i=0;i<7;i++){
    pre_end[i]=EFA(i);
  }

  heap_size+=MAX(size,CHUNKSIZE);
  heap_end=(char *)sbrk(0);
  list_end=heap_end-8*WSIZE;
  PUT(HA(list_end),PACK(8,1));
  for(int i=0;i<7;i++){
    PUT(FLP(LE(i)),pre_end[i]);
    PUT(FLN(pre_end[i]),LE(i));
  }

  PUT(HA(old_list_end),PACK(MAX(size,CHUNKSIZE),0));
  PUT(FA(old_list_end),PACK(MAX(size,CHUNKSIZE),0));
  char *new_block=(char *)m_coalesce_pre(m_add_fl(old_list_end));
  return m_split(new_block,size);
}

void ff_free(void *addr){
  PUT(HA(addr),PACK(GET_SIZE(HA(addr)),0));
  PUT(FA(addr),PACK(GET_SIZE(FA(addr)),0));
  used_size-=GET_SIZE(HA(addr));
  m_coalesce_next(m_coalesce_pre(m_add_fl((char *)addr)));
}


void bf_free(void *addr){
  PUT(HA(addr),PACK(GET_SIZE(HA(addr)),0));
  PUT(FA(addr),PACK(GET_SIZE(FA(addr)),0));
  used_size-=GET_SIZE(HA(addr));
  m_coalesce_next(m_coalesce_pre(m_add_fl((char *)addr)));
}


void wf_free(void *addr){
  PUT(HA(addr),PACK(GET_SIZE(HA(addr)),0));
  PUT(FA(addr),PACK(GET_SIZE(FA(addr)),0));
  used_size-=GET_SIZE(HA(addr));
  m_coalesce_next(m_coalesce_pre(m_add_fl((char *)addr)));
}

void m_free_noncoalesce(void *addr){
  PUT(HA(addr),PACK(GET_SIZE(HA(addr)),0));
  PUT(FA(addr),PACK(GET_SIZE(FA(addr)),0));
  used_size-=GET_SIZE(HA(addr));
  m_add_fl((char *)addr);
}


void *wf_malloc(size_t size){
  if(flag==0){
    m_init();
    flag = 1;
  }
  size=PADDING(size);
	char *worst_fit = EFA(6);
	int index = 6;
	while( (worst_fit==LS(index))&&(index>=0) ){
    index--;
		worst_fit = EFA(index);
	}

  if( (index==-1)||(GET_SIZE(HA(worst_fit))<size) ) {
    return m_expand(size);
  }
  else{
    if((worst_fit=m_split(worst_fit,size))!=NULL){
      return worst_fit;
    }
    else{
      printf("The find should find the right size block, but the split find the size is too small!\n");
      abort();
    }
  }
}
 



void *bf_malloc(size_t size){
  if(flag==0){
    m_init();
    flag = 1;
  }
  size=PADDING(size);
  char *current = FFA(m_fl_cal(size));
  while(current!=LE(m_fl_cal(size))){
    if((size_t)GET_SIZE(HA(current))>=size){
      break;
    }
    current=(char *)NFA(current);
  }
  if(current!=LE(m_fl_cal(size))){
    if((current=m_split(current,size))!=NULL){
      return current;
    }
    else{
      printf("The find should find the right size block, but the split find the size is too small!\n");
      abort();
    }
  }
  else{
			int index = m_fl_cal(size)+1;
			char *curr = FFA(index);
			while((curr == LE(index))&&(index<7)){
				index++;
				if(index>=7)
					break;
				curr = FFA(index);
			}
			if(index>=7){
				return m_expand(size);
			}
			else{
				if((curr=m_split(curr,size))!=NULL){
					return curr;
				}
				else{
					printf("The find should find the right size block, but the split find the size is too small!\n");
					abort();
				}
			}
  }
} 

void *ff_malloc(size_t size){
  if(flag==0){
    m_init();
    flag = 1;
  }
  size=PADDING(size);
  char *current = FFA(m_fl_cal(size));
  while(current!=LE(m_fl_cal(size))){
    if((size_t)GET_SIZE(HA(current))>=size){
      break;
    }
    current=(char *)NFA(current);
  }
  if(current!=LE(m_fl_cal(size))){
    if((current=m_split(current,size))!=NULL){
      return current;
    }
    else{
      printf("The find should find the right size block, but the split find the size is too small!\n");
      abort();
    }
  }
  else{
			int index = m_fl_cal(size)+1;
			char *curr = FFA(index);
			while((curr == LE(index))&&(index<7)){
				index++;
				if(index>=7)
					break;
				curr = FFA(index);
			}
			if(index>=7){
				return m_expand(size);
			}
			else{
				if((curr=m_split(curr,size))!=NULL){
					return curr;
				}
				else{
					printf("The find should find the right size block, but the split find the size is too small!\n");
					abort();
				}
			}
  }
} 


/*
void *ff_malloc(size_t size){
  if(flag==0){
    m_init();
    flag = 1;
  }
  size=PADDING(size);
  char *current = FFA(m_fl_cal(size));
  while(current!=LE(m_fl_cal(size))){
    if((size_t)GET_SIZE(HA(current))>=size){
      break;
    }
    current=(char *)NFA(current);
  }
  if(current!=LE(m_fl_cal(size))){
    if((current=m_split(current,size))!=NULL){
      return current;
    }
    else{
      printf("The find should find the right size block, but the split find the size is too small!\n");
      abort();
    }
  }
  else{
      return m_expand(size); 
  }
}
*/

void *m_coalesce_next(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  if( (GET_ALLOC(HA(NEXT_BLOCK(addr)))==0)&&(addr!=EFA(m_fl_cal(GET_SIZE(HA(addr))))) ){
    char * next_addr = NEXT_BLOCK(addr);
    size_t old_size = GET_SIZE(HA(addr));
    size_t new_size = old_size + GET_SIZE(HA(next_addr));
    int old_index = m_fl_cal(old_size);
    int new_index = m_fl_cal(new_size);

    char * pre_fl = (char *)PFA(next_addr);
    char * next_fl = (char *)NFA(next_addr);
    PUT(FLN(pre_fl),next_fl);
    PUT(FLP(next_fl),pre_fl);
    PUT(HA(addr),PACK(new_size,0));
    PUT(FA(addr),PACK(new_size,0));

    if(old_index!=new_index){
      char *pre = (char *)PFA(addr);
      char *next = (char *)NFA(addr);
      PUT(FLN(pre),next);
      PUT(FLP(next),pre);
      addr = m_add_fl(addr);
    }
  }
  return addr;
}

void *m_coalesce_pre(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  
  if( (GET_ALLOC(addr-DSIZE)==0)&&(PRE_BLOCK(addr)<heap_end)&&(PRE_BLOCK(addr)>heap_start)&&(GET_ALLOC(HA(PRE_BLOCK(addr)))==0)&&(GET_SIZE(HA(PRE_BLOCK(addr)))==GET_SIZE(addr-DSIZE))&&(addr!=FFA(m_fl_cal(GET_SIZE(HA(addr))))) ){
    char *pre_addr = PRE_BLOCK(addr);
    size_t old_size = GET_SIZE(HA(pre_addr));
    size_t new_size = GET_SIZE(HA(addr)) + old_size;
    int old_index = m_fl_cal(old_size);
    int new_index = m_fl_cal(new_size);
    char * pre_fl = (char *)PFA(addr);
    char * next_fl = (char *)NFA(addr);
    PUT(FLN(pre_fl),next_fl);
    PUT(FLP(next_fl),pre_fl);
    PUT(HA(pre_addr),PACK(new_size,0));
    PUT(FA(pre_addr),PACK(new_size,0));
    
    if(old_index!=new_index){
      char *pre = (char *)PFA(pre_addr);
      char *next = (char *)NFA(pre_addr);
      PUT(FLN(pre),next);
      PUT(FLP(next),pre);
      pre_addr = m_add_fl(pre_addr);
    }

    return pre_addr;
  }
  else
    return addr;
}
  
void *m_add_fl(char *addr){
  assert(GET_ALLOC(HA(addr))==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  
  int index = m_fl_cal(GET_SIZE(HA(addr)));
  char *current = FFA(index);
  while(current!=LE(index)){
    if(GET_SIZE(HA(current))>=GET_SIZE(HA(addr))){
      break;
    }
    current=(char *)NFA(current);
  }
  char * next_fl = current;
  char * pre_fl = (char *)PFA(current);

  PUT(FLP(next_fl),addr);
  PUT(FLN(addr),next_fl);
  PUT(FLN(pre_fl),addr);
  PUT(FLP(addr),pre_fl);
  return addr;
  
}

void *m_split(char *addr, size_t size){
  assert(size%16==0);
  assert((addr!=heap_start)||(addr!=list_start)||(addr!=list_end)||(addr!=heap_end));
  if(GET_SIZE(HA(addr))<size){
    printf("The block you find for split is too small  !");
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
    int old_index = m_fl_cal(GET_SIZE(HA(addr)));
    int new_index = m_fl_cal(new_size);
    PUT(HA(addr),PACK(size,1));
    PUT(FA(addr),PACK(size,1));
    used_size+=size;
    char *next_fl=(char *)NFA(addr);
    char *pre_fl=(char *)PFA(addr);
    char *rest_addr=NEXT_BLOCK(addr);
 
    PUT(HA(rest_addr),PACK(new_size,0));
    PUT(FA(rest_addr),PACK(new_size,0));
    if(old_index==new_index){
      PUT(FLN(pre_fl),rest_addr);
      PUT(FLP(rest_addr),pre_fl);
      PUT(FLP(next_fl),rest_addr);
      PUT(FLN(rest_addr),next_fl);
    }
    else{
      PUT(FLN(pre_fl),next_fl);
      PUT(FLP(next_fl),pre_fl);
      m_add_fl(rest_addr);
    }
    return addr;
  }
}
/*
struct malloc_list {
  size_t bytes;
  int *address;
};
typedef struct malloc_list malloc_list_t;

malloc_list_t malloc_items[2][NUM_ITEMS];

unsigned free_list[NUM_ITEMS];


int main(int argc, char *argv[])
{
  int i, j, k;
  unsigned tmp;
  unsigned long data_segment_size;
  unsigned long data_segment_free_space;
  struct timeval start_time, end_time;

  srand(0);

  const unsigned chunk_size = 32;
  const unsigned min_chunks = 1;
  const unsigned max_chunks = 2048;
  for (i=0; i < NUM_ITEMS; i++) {
    malloc_items[0][i].bytes = ((rand() % (max_chunks - min_chunks + 1)) + min_chunks) * chunk_size;
    malloc_items[1][i].bytes = ((rand() % (max_chunks - min_chunks + 1)) + min_chunks) * chunk_size;
    free_list[i] = i;
  } //for i

  i = NUM_ITEMS;
  while (i > 1) {
    i--;
    j = rand() % i;
    tmp = free_list[i];
    free_list[i] = free_list[j];
    free_list[j] = tmp;
  } //while


  for (i=0; i < NUM_ITEMS; i++) {
    malloc_items[0][i].address = (int *)MALLOC(malloc_items[0][i].bytes);
  } //for i


  //Start Time
  gettimeofday(&start_time, NULL);

  for (i=0; i < NUM_ITERS; i++) {
    unsigned malloc_set = i % 2;
    for (j=0; j < NUM_ITEMS; j+=50) {
      for (k=0; k < 50; k++) {
	unsigned item_to_free = free_list[j+k];
	FREE(malloc_items[malloc_set][item_to_free].address);
      } //for k
      for (k=0; k < 50; k++) {
	malloc_items[1-malloc_set][j+k].address = (int *)MALLOC(malloc_items[1-malloc_set][j+k].bytes);
      } //for k
    } //for j
  } //for i

  //Stop Time
  gettimeofday(&end_time, NULL);

  data_segment_size = get_data_segment_size();
  data_segment_free_space = get_data_segment_free_space_size();

  double elapsed_sec = calc_time(start_time, end_time);
  printf("Execution Time = %f seconds\n", elapsed_sec);
  printf("Fragmentation  = %f\n", (float)data_segment_free_space/(float)data_segment_size);

  for (i=0; i < NUM_ITEMS; i++) {
    FREE(malloc_items[0][i].address);
  } //for i

  return 0;
}


*/
