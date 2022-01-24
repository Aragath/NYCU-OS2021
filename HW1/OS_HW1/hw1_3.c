#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE 80

void dealArg(char inputBuffer[], char *arg[], int *should_run);

int main(void)
{
	char *arg[MAX_LINE/2+1]; /* command line arguments */
	char inputBuffer[MAX_LINE];
	int should_run = 1; /* flag to determine when to exit program */
	pid_t pid;

	while(should_run){
		memset(inputBuffer, 0, sizeof(inputBuffer)); // clean array
		memset(arg, 0, sizeof(arg));
		printf("osh>");
		fflush(stdout);
		read(STDIN_FILENO, inputBuffer, MAX_LINE); // read command line
		dealArg(inputBuffer, arg, &should_run);
		//printf("in main the args: %s %s\n", arg[0], arg[1]);
		pid = fork();
		if(pid > 0)
			wait(NULL);
		else if(pid == 0){
			execvp(arg[0], arg);
		}
	}
	
	return 0;
}

void dealArg(char inputBuffer[], char *arg[], int *should_run)
{
  	char * pch;
	int i = 0;
  	//printf ("Splitting string %s\n",inputBuffer);
  	pch = strtok (inputBuffer," \n");
  	while (pch != NULL){
    		//printf ("%s\n",pch);
		arg[i] = pch;
		i++;
    		pch = strtok (NULL, " \n");
  	}
	//printf("this is arg[0]: %s\n", arg[0]);
	//printf("this is arg[1]: %s\n", arg[1]);
	arg[i] = NULL;
	//printf("this is arg[2]: %s\n", arg[2]);
	if(strcmp(arg[0], "exit") == 0){
		*should_run = 0;
	}
	

}
