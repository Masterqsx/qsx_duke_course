#include <iostream>
#include <stdio.h>
using namespace std;
int main(void) {
  int a = 3;
  int b = 9;
  FILE *out;
  out = fopen("answer.txt","w");
  while (a <= b) {
     if (a % 2 == 1) {
        fprintf(out,"a is %d\n", a);
     }
     else {
       fprintf(out,"b is %d\n", b);
       for (int i = 0; i < b - a ; i++) {
         fprintf(out,"a * i + b = %d\n", a * i + b);
       }
     }
     a++;
     b--;
  }  
 return 0;
}


