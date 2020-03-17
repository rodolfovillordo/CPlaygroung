#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP "127.0.0.1"
#define PORT 8080

void fatal(char *s)
{
	fprintf(stderr, "ERROR %s\n", s);
	exit(1);
}

int main( int argc, char *argv[])
{
	char *message = malloc(100*sizeof(char));
	int sfd;
	struct sockaddr_in srv_ip;

	if(argc < 2){
		printf("usage %s <message>\n",argv[0]);
		return -1;
	}
	
	memset(message, 0, 100);
	memcpy(message, argv[1], strlen(argv[1]));

	srv_ip.sin_family = AF_INET;
	srv_ip.sin_port = htons(PORT);
	if(inet_pton(AF_INET, IP, &srv_ip.sin_addr) < 0)
		fatal("unable to convert server IP");

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		fatal("creating socket");

	if(connect(sfd, (struct sockaddr *)&srv_ip, sizeof(srv_ip)) < 0)
		fatal("connecting to server");

	send(sfd, message, 100, 0);
	printf("Sent message: %s\n", message);
	memset(message, 0, 100);
	read(sfd, message, 100);
	printf("got: %s\n", message);
	return 0;
}
