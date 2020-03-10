#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define IP "127.0.0.1"
#define PORT 8080
#define MAX_CLIENT 10

void fatal(char *s)
{
	fprintf(stderr, "ERROR: %s\n",s);
	exit(1);

}

void* response (void *message)
{
	char *u_message;
	int i = 0;
	u_message = malloc(strlen(message)*sizeof(char));
	while(message){
		u_message = toupper(message[i]);
		i++;
		messsage++;
	}
	return u_message;
}
