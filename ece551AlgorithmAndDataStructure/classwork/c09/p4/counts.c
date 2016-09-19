#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * new=malloc(sizeof(*new));
  new->length=0; new->unknown_count=0; new->array=NULL;
  return new;
}

int exist(counts_t * c, const char* name, int *index)
{
	for(int i=0;i<c->length;i++)
	{
		if(strcmp(c->array[i].string,name)==0)
		{
			*index=i;
			return 1;
		}
	}
	return 0;
}

char * stringcpy(const char* name)
{
	int i=0; char *new;
	while(name[i]!='\0')
	{
		i++;
	}
	new=malloc((i+1)*sizeof(*new));
	strcpy(new,name);
	return new;
}

void addCount(counts_t * c, const char * name) 
{
  int index=0;
  if(name!=NULL)
  {
	char *filename=stringcpy(name);
	if(exist(c,filename,&index))
	{
		c->array[index].num+=1;
		free(filename);
	}
	else
	{
  		c->length+=1;
  		c->array=realloc(c->array,c->length*sizeof(*c->array));
		c->array[c->length-1].string=filename;
		c->array[c->length-1].num=1; 
	}
  }
  else
	c->unknown_count+=1;
}

void printCounts(counts_t * c, FILE * outFile) {
  for(int i=0;i<c->length;i++)
  {
	fprintf(outFile,"%s: %d\n",c->array[i].string,c->array[i].num);
  }
  if(c->unknown_count!=0)
  	fprintf(outFile,"<unknown> : %d\n",c->unknown_count);

}

void freeCounts(counts_t * c) {
  for(int i=0;i<c->length;i++)
  {
	free(c->array[i].string);
  }
  free(c->array);
  free(c);
}
