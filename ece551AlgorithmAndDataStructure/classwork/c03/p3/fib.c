#include<stdio.h>



int fib(int n)
{
	int sum=0,sum1=1,sum0=1;
	if( n<=0 )
	{
		return 0;
	}
	else if(n==1)
	{
		return 1;
	}
	else if(n==2)
	{
		return 1;
	}
	else
	{
		for( int i=0;i<=n-3;i++ )
		{
			sum=sum0+sum1;
			sum0=sum1;
			sum1=sum;
		}
	}
	return sum;
}
		

int main()
{
	for( int i=-2;i<=30;i++ )
	{
		printf("fib(%d) = %d\n",i,fib(i));
	}
	return 0;
}	
