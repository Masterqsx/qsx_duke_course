#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
    //print the counts from c into the FILE f
#include "counts.h"
#include "outname.h"
char * enter_remove(char *line)
{
	int i=0;
	while(line[i]!='\n')
	{
		i++;
	}
	line[i]='\0';
	line=realloc(line,(i+1)*sizeof(*line));
	return line;
}

char ** string_read(FILE *f, int * count)
{
	char *line=NULL; size_t sz=0; char ** data=NULL;*count=0;
	while(getline(&line,&sz,f)>=0)
	{
		line=enter_remove(line);
		*count+=1;
		data=realloc(data,*count*sizeof(*data));
		data[*count-1]=line;
		line=NULL;
	}
	free(line);
	line=NULL;
	
	return data;		
}

void free_string_read(char **data, int count)
{
	for(int i=0;i<count;i++)
	{
		free(data[i]);
		data[i]=NULL;
	}
	free(data);
	data=NULL;
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f=fopen(filename,"r"); int count=0;
  counts_t * file_value_count=createCounts();
  char ** data = string_read(f, &count);
  for(int i=0;i<count;i++)
  {
	addCount(file_value_count,lookupValue(kvPairs,data[i]));
  }
  free_string_read(data,count);  
  fclose(f);
  return file_value_count;
}

int main(int argc, char ** argv) {

  if(argc<=2)
  {
	fprintf(stderr,"Please enter the write filename\n");
	return EXIT_FAILURE;
  }
  kvarray_t * file_pairs=readKVs(argv[1]);
  counts_t * file_value_count=NULL;
  FILE * output=NULL;char *output_filename=NULL;
  for(int i=2;i<argc;i++)
  {
	output_filename=computeOutputFileName(argv[i]);
	output=fopen(output_filename,"w");
	file_value_count=countFile(argv[i],file_pairs);
	printCounts(file_value_count, output);
	fclose(output);
	output=NULL;
	freeCounts(file_value_count);
	free(output_filename);
	output_filename=NULL;
  }
  freeKVs(file_pairs); 
		  
  return EXIT_SUCCESS;
}
