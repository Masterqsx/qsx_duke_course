#include<stdio.h>                          
int f(int x) {                   //line 2 
  int answer = 0                 //line 3 missing ';'
  for (int i = 0; i < X; i++) {  //line 4 no declaration for 'X'
    answer += i * i;             //line 5
  }                              //line 6
  return answer;                 //line 7
                                 //line 8 missiong '}'
