#include <stdio.h>
#include <stdlib.h>



int * initArray(int * array, int n){
  for (int i = 0; i < n; i++){
    array[i] = i;
  }
  return array;
}

int * aFunction(int n,int * r_myArray) {
  int myArray[n];
  
  int * ptr = initArray(myArray, n-1);
  int total = 0;
  for (int i = 0; i <n; i++) {
    printf("%d\n", myArray[i]);
    total += ptr[i];
  }
  printf("Total = %d\n", total);
  r_myArray=myArray;
  return r_myArray;
}

int main (void) {
  int * in;
  int * ptr = aFunction(8,in);
  printf("%d\n", ptr[0]);
  return EXIT_SUCCESS;
}
