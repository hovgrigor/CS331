#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void cool_func_1() { printf("I the first func did something, maybe \n"); };
void cool_func_2() { printf("I the second func did something too, maybe \n"); };

int main() {
  atexit(cool_func_1);
  atexit(cool_func_2);
  exit(1);
  return 0;
}
