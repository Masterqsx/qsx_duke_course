#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void free_malloc(char ** data, size_t count)
{
	for(int i=0;i<count;i++)
	{
		free(*(data+i));
	}
	free(data);
}
void output(char ** data, size_t count)
{
	sortData(data,count);
	for(int i=0;i<count;i++)
	{
		printf("%s",*(data+i));
	}
}

char ** read(char * line,size_t sz,FILE *f,size_t * count)
{
	char **data=NULL;
	*count = 0;
	while( getline(&line,&sz,f)>=0)
	{
		
		*count+=1;
		data=realloc(data,*count*sizeof(char *));
		*(data+*count-1)=line;
		line=NULL;
	}
	free(line);
	return data;
}

int main(int argc, char ** argv) {
  char * line=NULL;
  size_t sz=0,count=0;
  char ** data=NULL;
  FILE * f=NULL;
  if(argc==1)
  {
//	while( getline(&line,&sz,stdin)>=0)
//	{
//		
//		count+=1;
//		data=realloc(data,count*sizeof(char *));
//		*(data+count-1)=line;
//		line=NULL;
//	}
//	free(line);
	data=read(line,sz,stdin,&count);
	output(data,count);
	free_malloc(data,count);
  }
  else
  {
	for(int k=1;k<argc;k++)
	{
		data=NULL;
		line=NULL;
		count=0;
		f=fopen(argv[k],"r");
		if(f==NULL)
		{
			perror("Could not open file");
			return EXIT_FAILURE;
		}
		while( getline(&line,&sz,f)>=0)
		{
			count+=1;
			data=realloc(data,count*sizeof(char *));
			*(data+count-1)=line;
			line=NULL;
		}
//    free(line);
		output(data,count);
		free_malloc(data,count);
		if(fclose(f)!=0)
		{
			perror("Failed to close the input file!");
			return EXIT_FAILURE;
		}
	}
}
  return EXIT_SUCCESS;
}
