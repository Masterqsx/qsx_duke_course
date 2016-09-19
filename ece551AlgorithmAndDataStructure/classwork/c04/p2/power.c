#include<stdio.h>



unsigned power(unsigned x,unsigned y)
{
	if((x==0)&&(y==0))
	{
		return 1;
	}
	else if(x==0)
	{
		return 0;
	}
	if(x==1)
	{
		return 1;
	}
	if(y==0)
	{
		return 1;
	}
	else if(y==1)
	{
		return x;
	}
	else
	{
		return (x*power(x,y-1));
	}
}
int main()
{
	int x,y,f=0;
	scanf("%d %d %d",&x,&y,&f);
	if(f!=0)
	{
		printf("you choose to quit\n");
		return 0;
	}
	if(x<0)
	{
		x=0-x;
	}
	if(y<0)
	{
		printf("you can not enter minous y\n");
		return 0;
	}
	printf("%u\n",power(x,y));
	return 0;
} 	
