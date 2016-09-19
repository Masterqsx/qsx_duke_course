#include<stdio.h>
#include<stdlib.h>

struct _test
{
	int a;
	int b;
};

typedef struct _test test;

int main(){
	test c={1,2};
	test *e=&c;
	int x[2][2]={{1,2},{3,4}};
	int *y=0x000;
	int (*d)[2][2];
	d=&x;
	y=y+1;
	printf("%d\n%d\n",e->a,x[0][0]);
  printf("%d\n%p\n%p\n",***d,d,&d);
	return 0;
}
