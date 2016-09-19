#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
	int i=0; char * OutputFileName=NULL;
  if(inputName!=NULL)
  {
	while(inputName[i]!='\0')
	{
		i++;
		OutputFileName=realloc(OutputFileName, i*sizeof(*OutputFileName));
		OutputFileName[i-1]=inputName[i-1];
	}
	OutputFileName=realloc(OutputFileName,(i+1)*sizeof(*OutputFileName));
	OutputFileName[i]='\0';
	OutputFileName=realloc(OutputFileName,(i+8)*sizeof(*OutputFileName));
	strcat(OutputFileName,".counts");
	return OutputFileName;
   }
   else
	return NULL;
}

