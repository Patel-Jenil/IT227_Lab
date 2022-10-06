#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");
  char s[256];
  int c = atoi(argv[2]);
  while (c--)
    fgets(s, 256, f);
  printf("%s", s);
  fclose(f);
  return 0;
}
