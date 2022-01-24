#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	printf("current process pid: %d\n", getpid());
	pid = fork(); // fork0
	printf("************after fork0************\n");
	printf("current process pid: %d\n", getpid());
	printf("current process's parent pid: %d\n", getppid());
	if(pid == 0){
		pid = fork(); // fork1
		printf("************after fork1************\n");
		printf("current process pid: %d\n", getpid());
		printf("current process's parent pid: %d\n", getppid());
		if(pid > 0)
			wait(NULL);
		pid = fork(); // fork2
		printf("************after fork2************\n");
		printf("current process pid: %d\n", getpid());
		printf("current process's parent pid: %d\n", getppid());
		if(pid > 0)
			wait(NULL);
	}
	else if(pid >0){
		wait(NULL);
		pid = fork(); // fork3
		printf("************after fork3************\n");
		printf("current process pid: %d\n", getpid());
		printf("current process's parent pid: %d\n", getppid());
		if(pid > 0)
			wait(NULL);
	}
	else{
		printf("Error!");
	}
	pid = fork(); // fork4
	printf("************after fork4************\n");
	printf("current process pid: %d\n", getpid());
	printf("current process's parent pid: %d\n", getppid());
	if(pid > 0)
		wait(NULL);
	return 0;
}
		
