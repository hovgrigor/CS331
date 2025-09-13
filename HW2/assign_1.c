#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
        int a = fork();
        if(a == 0){
	execl("/bin/ls", "ls", "-l", NULL);
        } else {
	wait(NULL);	
        printf("Parent process done");
        };
	return 0;
}

