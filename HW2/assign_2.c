#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        execl("/bin/ls", "ls", NULL);
    }
    pid2 = fork();
    if (pid2 == 0) {
        execl("/bin/date", "date", NULL);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("Parent process done\n");
    return 0;
}
