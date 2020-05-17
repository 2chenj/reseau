#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <strings.h>
#include <string.h>
int main(int argc, char *argv[])
{
	char *hello = "hello from client";
	struct sockaddr_in server = {0};

	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd ==-1) {
		perror("failed to create a socket");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(9600);
	server.sin_addr.s_addr = INADDR_ANY;
		
	int len = sendto(sockfd,(const char *)hello,strlen(hello),0,(const struct sockaddr *)&server, sizeof(server));

	if (len ==-1) {
		perror("failed to send");
	}

	close(sockfd);
	return 0;
}
