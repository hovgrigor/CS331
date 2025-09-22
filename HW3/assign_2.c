#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int status1;
  int status2;
  int a = fork();
  if (a == 0) {
    printf("Child pid -> %d \n", getpid());
    exit(0);
  };
  wait(&status1);
  printf("Child exit code -> %d \n", WEXITSTATUS(status1));

  int b = fork();
  if (b == 0) {
    printf("Better Child pid -> %d \n", getpid());
    exit(125);
  }
  waitpid(b, &status2, 0);
  printf("Better Child exit code -> %d \n", WEXITSTATUS(status2));
};
