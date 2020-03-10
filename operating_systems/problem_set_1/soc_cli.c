#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER "127.0.0.1"
#define PORT 8888

int main(void)
{
	int r = 0;
	int sock = 0;
	int count_r = 0;
	char buff[1024] = "span\0";

	struct sockaddr_in serv;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR unable to create the socket\n");
		exit(1);
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);

	if (inet_pton(AF_INET, SERVER, &serv.sin_addr) <= 0) {
		printf("ERROR unable to convert server address\n");
		exit(1);
	}

	if (connect(sock, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
		printf("ERROR unable to connect to server %s on port %d\n",
				SERVER, PORT);
		exit(1);
	}
	while (strlen(buff) > 0) {
		send(sock,buff,strlen(buff),0);
		count_r = read(sock, buff, 1000);
		buff[count_r+1] = '\0';
		printf("server: %s\n", buff);
		fflush(stdin);
		fgets(buff, 1000, stdin);
	}
	return 0;

}
