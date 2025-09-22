#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void status_check(int status) {
  int status_code = WEXITSTATUS(status);
  if (!status_code) {
    printf("Status -> %d (Exited with success) \n", status_code);
  } else {
    printf("Status -> %d (Exited with failure) \n", status_code);
  };
}

int main() {
  int status1;
  int status2;
  int a = fork();
  if (a == 0) {
    exit(0);
  };
  waitpid(a, &status1, 0);
  status_check(status1);
  int b = fork();
  if (b == 0) {
    exit(125);
  }
  waitpid(b, &status2, 0);
  status_check(status2);
  return 0;
};
