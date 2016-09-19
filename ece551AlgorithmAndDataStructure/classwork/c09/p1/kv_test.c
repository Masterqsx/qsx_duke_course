#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

#define NUM_LOOKUPS 5
int main(void) {
  kvarray_t * nullarray = readKVs(NULL);
  kvarray_t * array = readKVs("test.txt");
  printf("Printing all keys\n\n");
  printKVs(array);
  printKVs(nullarray);
  char *tests[NUM_LOOKUPS] = {"banana", "grapes", "cantaloupe", "lettuce", "orange"};
  //lookupValue(array,NULL);
  printf("%s \n",lookupValue(array,""));
  for (int i = 0; i < NUM_LOOKUPS; i++) {
    printf("lookupValue('%s')=%s\n", tests[i], lookupValue(array,tests[i]));
  }
  freeKVs(nullarray);
  freeKVs(array);
  return EXIT_SUCCESS;
}
