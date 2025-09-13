#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>

int main() 
{ 
	int a = fork();
 	if(a == 0){
	printf("First Fork: I am a child my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	} else {
	waitpid(a, NULL, 0);
	printf("First Fork: I am a parent my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	};
        int b = fork();
 	if(b == 0){
	printf("Second Fork: I am a child my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	} else {
	waitpid(b, NULL, 0);
	printf("Second Fork: I am a parent my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	};
        int c = fork();
 	if(c == 0){
	printf("Third Fork: I am a child my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	} else {
	waitpid(c, NULL, 0);
	printf("Third Fork: I am a parent my proccess id %ld; my parent process id %ld\n", (long)getpid(), (long)getppid());
	};
        return 0; 
} 
