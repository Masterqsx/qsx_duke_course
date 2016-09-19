#include <stdio.h>
#include <stdlib.h>

int whether_is_prime(int n)
{
	int i;
	if(n<=1)
	{
		return 0;
	}
	else if(n==2)
	{
		return 1;
	}
	else if(n%2==0)
	{
		return 0;
	}
	
	for(i=2;i<=n/2+1;i++)
	{
		if(n%i==0)
		{
			return 0;
		}
	}
	return 1;
}

void printFactors(int n) 
{
	int cn=n;
	int i,flag=0;
	if(whether_is_prime(n))
	{
		printf("%d",n);
	}	
	else if(n<=1)
	{
	}
	else
	{
	while(cn!=1)
	{
		for(i=2;i<=n/2+1;i++)
		{
			if( (cn%i==0)&&(flag!=0)&&whether_is_prime(i) )
			{ 
				printf(" * %d",i);
				cn=cn/i;
				break;
			}
			else if( (cn%i==0)&&(flag==0)&&whether_is_prime(i) )
			{
				printf("%d",i);
				cn=cn/i;
				flag=1;
				break;
			}
		}
	}
	}
	printf("\n");
}
					  


int main(void) {
  printf("Factorization of 1:\n");
  printFactors(1);
  printf("Factorization of 2:\n");
  printFactors(2);
  printf("Factorization of 3:\n");
  printFactors(3);
  printf("Factorization of 6:\n");
  printFactors(6);
  printf("Factorization of 2169720:\n");
  printFactors(2169720);
  printf("Factorization of 1789220887:\n");
  printFactors(1789220887);
  return EXIT_SUCCESS;
}
