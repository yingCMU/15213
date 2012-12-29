#include <stdio.h>
    #include <stdlib.h> /* for atoi() */

    int main(int argc,char *argv[]) {
  int size=atoi(argv[1]);
  char buff[size];
  printf("input\n");
  gets(buff);
return 0;
}
