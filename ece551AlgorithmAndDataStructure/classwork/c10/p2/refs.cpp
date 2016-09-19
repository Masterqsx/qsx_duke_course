#include <stdio.h>
#include <stdlib.h>

int & f(int * ptr, int & r) {
  r ++;
  ptr[3] += r;
  return ptr[1];
}

int main(void) {
  int data[] = {6, 7, 8, 9,10};
  int & x = data[1]; //x=7 ->data[1]
  x = data[2];       //{6,8,8,9,10}
  int * p = &x;      //p->data[1]
  f(p, data[3]) = 47;//{6,8,47,10,20}
  for (int i = 0; i < 5; i++) {
    printf("data[%d] = %d\n", i, data[i]);
  }
  printf("x = %d\n", x);//data[1] 8
  return EXIT_SUCCESS;
}
