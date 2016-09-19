#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strsort(const char ** strarray, int n) {
	const char *temp=NULL;int i=0;int j=0;
	for(i=0;i<n;i++){
	  for(j=0;j<n-1-i;j++){
	    if( strcmp(strarray[j],strarray[j+1])>0 ){
 		temp=strarray[j];
		strarray[j]=strarray[j+1];
		strarray[j+1]=temp;
	    }
	  }
	}
}

void print_array(const char ** strarray, int n) {
  for (int i =0 ; i < n; i++) {
    printf("%d: %s\n", i, strarray[i]);
  }
}

int main(void) {
  const char * array1[8] = {"zucchini", "cake", "bread", "grapes", "french fries", "apples", "diced peaches", "eggplant"};
  strsort(array1,8);
  print_array(array1,8);

  return 0;
}
