#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void t_function(int number_t, char *cmd) 
{
	char *newenv[] = { NULL };
	char *newargv[] = { NULL, NULL};

	newargv[0] = cmd;
	
	if (number_t == 2) 
		execve(cmd, newargv, newenv);

	sleep(30);
	
}

int main(int argc, char* argv[]) 
{
	if (argc < 2){
		fprintf(stdout,"Usage: %s <file-to-exec> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	t_function(2, argv[1]);
}

