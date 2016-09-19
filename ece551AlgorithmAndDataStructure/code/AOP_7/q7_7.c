#include<stdio.h>
#include<stdlib.h>

void printhex(int a){
	if(a==0){
		return;
	}
	else
		printhex(a/16);
	printf("%x",a%16);
}

int main(){
	printhex(255);
	printf("\n");
	return 0;
}
