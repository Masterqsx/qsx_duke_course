#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, stdin) >= 0) {
    int x = atoi(line);
    printf("%d*%d = %d\n", x, x, x*x);
  }
  free(line);
  return EXIT_SUCCESS;
}
