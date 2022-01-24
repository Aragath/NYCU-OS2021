#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	printf("Main Process ID: %d \n\n", getpid());
	pid = fork(); // fork1
	if(pid == 0){
		printf("Fork 1. I'm the child %d, my parent is %d.\n", getpid(), getppid()); // 1
		pid = fork(); // fork4
		if(pid > 0)
			wait(NULL);
		else if(pid == 0){
			printf("Fork 4. I'm the child %d, my parent is %d.\n", getpid(), getppid()); // 2
			pid = fork(); // fork5
			if(pid > 0)
				wait(NULL);
			else if(pid == 0){
				printf("Fork 5. I'm the child %d, my parent is %d.\n", getpid(), getppid()); // 3
			}
		}
	}
	else if(pid > 0){
		wait(NULL);
		pid = fork(); // fork2
		if(pid > 0)
			wait(NULL);
		else if(pid == 0){
			printf("Fork 2. I'm the child %d, my parent is %d.\n", getpid(), getppid()); // 4
		}
		pid = fork(); // fork3
		if(pid > 0){
			wait(NULL);
		}
		else if(pid == 0){
			printf("Fork 3. I'm the child %d, my parent is %d.\n", getpid(), getppid()); // 5, 6
		}
	
	}
	else{
		printf("error\n");
	}
	return 0;
}
		
