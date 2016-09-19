#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void rotation(FILE *f, char * af)
{
	char c;
	int i=0,j=0;
	while ((c=fgetc(f))!=EOF)
	{
		if(c=='\n')
		{  i++; j=0;  }
		else
		{
		   
		   *(af+j*10+9-i)=c;
		   j++;
		}
	}
} 
		

int main(int argc, char ** argv)
{
	int i,j;
	if(argc!=2)
	{
		fprintf(stderr,"Usage: only input the filename\n");
		return EXIT_FAILURE;
	}
	FILE * f = fopen(argv[1],"r");
	if (f == NULL)
	{
		perror("Could not open file");
		return EXIT_FAILURE;
	}
	char after_rotation[10][10];
	rotation(f,(char *)after_rotation);
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%c",after_rotation[i][j]);
		}
		printf("\n");
	}
	if(fclose(f)!=0)
	{
		perror("Failed to close the input file!");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
