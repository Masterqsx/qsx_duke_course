#include<stdlib.h>
#include<stdio.h>

typedef struct retire_info
{
	int month;
	double contribution;
	double rate;
} retire_info;

void retirement(int startAge, double initial ,retire_info working, retire_info retired)
{
	int i;
	double balance=initial;
	for (i=0;i<working.month+retired.month;i++)
	{
		if(i<working.month)
		{
			printf("Age %3d month %2d you have $%.2lf\n",(startAge+i)/12,(startAge+i)%12,balance);
			balance=balance*(1+working.rate)+working.contribution;
		}
		else 
		{
			printf("Age %3d month %2d you have $%.2lf\n",(startAge+i)/12,(startAge+i)%12,balance);
			balance=balance*(1+retired.rate)+retired.contribution;
		}
	}
}
	
int main()
{
	int st=327;
	double ini=21345;
	retire_info wo,re;
	wo.month=489;
	wo.contribution=1000;
	wo.rate=0.045/12;
	re.month=384;
	re.contribution=-4000;
	re.rate=0.01/12;
	retirement(st,ini,wo,re);
}
