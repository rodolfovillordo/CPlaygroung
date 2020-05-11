#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/un.h>

#define IP "127.0.0.1"
#define PORT 8888
#define LISTEN_BACKLOG 1



void* chat(void *client)
{


}

void fatal(char *message)
{
	printf("ERROR: %s\n", message);
	exit(1);
}
int main (void)
{
	int r, sock, cfd;

	char buff[1024] = "spam\0";
	struct sockaddr_in srv_a;
	struct sockaddr_in peer_a;
	socklen_t peer_a_size;

	if ( (sock = socket(AF_INET, SOCK_STREAM,0)) < 0)
		fatal("socket creation failled");

	srv_a.sin_family = AF_INET;
	srv_a.sin_port = htons(PORT);

	if ( inet_pton(AF_INET, IP, &srv_a.sin_addr) <= 0) 
		fatal("invalid IP address");	

	if (bind(sock, (struct sockaddr *)&srv_a, sizeof(srv_a)) < 0)
		fatal("unable to bind on socket");

	if(listen(sock, LISTEN_BACKLOG) < 0)
		fatal("unable to listen on socket");

	peer_a_size = sizeof(struct sockaddr_un);
	if ((cfd = accept(sock, (struct sockaddr *)&srv_a, &peer_a_size)) < 0)
		fatal("unable to accept the connection");
		
	while(strlen(buff) > 0){
		r = read(cfd, buff, 1000);
		buff[r+1] = '\0';
		printf("client: %s\n", buff);
		fflush(stdin);
		fgets(buff, 1000, stdin);
		send(cfd, buff, strlen(buff), 0);
	}

}

