#include<stdio.h>
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

int main()
{
	int number;
	scanf("%d",&number);
	printf("%d\n",whether_is_prime(number));

	return 0;
}
	
