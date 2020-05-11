#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>

#define IP "127.0.0.1"
#define PORT 8080
#define MAX_CLIENT 1

void fatal(char *s)
{
	fprintf(stderr, "ERROR: %s\n",s);
	exit(1);
}

void up_string(char message[])
{
	int i = 0;
	while(i < strlen(message)){
		message[i] = toupper(message[i]);
		i++;
	}
}

int main (void)
{
	int sfd;
	int cfd;
	int rb;
	int i, addr_size;
	char buff[1024];
	struct sockaddr_in addr;

	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	if(inet_pton(AF_INET, IP, &addr.sin_addr) < 0)
		fatal("Unable to convert server IP");

	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
		fatal("unable to create socket");

	if(bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		fatal("unable to bind socket");

	if(listen(sfd, MAX_CLIENT) < 0)
		fatal("unable to listen on socket");
	i = 0;
	addr_size = sizeof(struct sockaddr_un);
	cfd = accept(sfd, NULL, NULL);
	rb = read(cfd, buff, 1000);
	up_string(buff);
	send(cfd, buff, sizeof(buff), 0);
	close(cfd);

	return 0;
}
