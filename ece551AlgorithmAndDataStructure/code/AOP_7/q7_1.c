#include<stdio.h>
#include<stdlib.h>

int pascal(int i,int j){
	if(j>i){
		return 0;
	}
	if(j==0){
		return 1;
	}
	if(i==j){
		return 1;
	}
	return pascal(i-1,j-1)+pascal(i-1,j);
}

int main(int args,char **argv){
	if(args!=3){
		fprintf(stderr,"invalid input argument\n");
		return 1;
	}
	printf("%d\n",pascal(atoi(argv[1]),atoi(argv[2])));
	return 0;
}
	
	
