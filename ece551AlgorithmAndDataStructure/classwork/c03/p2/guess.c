#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//These are defined elsehwere..
int getSecretNumber(void);
int readANumber(void);
char * getSecretWord(void);
char * readWord(void);

int main(void) {
  printf("Hello, we are going to play a guessing game!\n");
  int num= getSecretNumber();
  int yourNum;
  do {
    printf("What number do you guess? ");
    yourNum = readANumber();
  }  while(yourNum != num);
  printf("Correct!  Now we play another game!\n");
  printf("Guess the magic words!\n");
  char * secretword = getSecretWord();
  char * yourword;
  do {
    printf("What words do you guess?  ");
    yourword = readWord();
  } while(strcmp(yourword, secretword) != 0);
  printf("Very good (do you know the movie that references?)\n");
  return EXIT_SUCCESS;
}
