#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int a = fork();
  if (a == 0) {
    printf("Child pid -> %d \n", getpid());
    exit(0);
  };
  printf("Parent pid -> %d \n", getpid());
}
