#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int a = fork();
  if (a == 0) {
    printf("Child started \n");
    exit(0);
  };
  sleep(30);
  printf("Parent done\n");
}
