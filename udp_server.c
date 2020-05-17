#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <strings.h>
int main(int argc, char *argv[])
{
	char buffer[50] = {0};
	struct sockaddr_in server = {0};	

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd==-1) {
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(9600);
	server.sin_addr.s_addr = INADDR_ANY;

	int rc=bind(sockfd,(const struct sockaddr *)&server,sizeof(server));

	if (rc==-1) {
		perror("failed to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	while(1){
		socklen_t len = 0;
		int n = recvfrom(sockfd,(char *)buffer, 50, MSG_WAITALL,0,&len);
		buffer[n]= '\n';
		printf("%s\n", buffer);
	}
	close(sockfd);

	return 0;
}
