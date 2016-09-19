#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void decrypt(FILE * f, int key)
{
	int c;
	while ((c = fgetc(f)) != EOF)
	{
		if (isalpha(c))
		{
			c=tolower(c);
			c-= 'a';
			c+= key;
			c %= 26;
		        c+= 'a';
		}
	//	printf("%c", c);
	}
}

int key_count(FILE * f)
{
	int fre[26]={0};
	int c,i,max,key;
	while ((c = fgetc(f)) != EOF)
	{
		if (isalpha(c))
		{
			c=tolower(c);
			fre[c-'a']++;
		}
	}
	max=fre[0];
	key=0;
	for(i=1;i<26;i++)
	{
		if(fre[i]>max)
		{
			max=fre[i];
			key=i;
		}
	}
	fseek(f,0,SEEK_SET);
	if(key<=4)
	{
	//	printf("Complement key is %d\n",4-key);
		fprintf(stdout,"%d\n",22+key);
		return 4-key;
	}
	else
	{
	//	printf("Complement key is %d\n",30-key);
		fprintf(stdout,"%d\n",key-4);
		return 30-key;
	}
}

int main(int argc, char ** argv)
{


	if(argc !=2)
	{
		fprintf(stderr,"Usage: enter only the inputFileName\n");
		return EXIT_FAILURE;
	}
	FILE * f = fopen(argv[1], "r");
	if(f==NULL)
	{
		perror("Could not open file");
		return EXIT_FAILURE;
	}
	decrypt(f,key_count(f));
	if (fclose(f) !=0)
	{
		perror("Failed to close the input file!");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
		
