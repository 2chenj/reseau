
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

//++
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	//socket
	//bind
	//listen
	//accept
	int serverPort = atoi(argv[1]);	
	int serverSocket, bindStatus;
	struct sockaddr_in server;
	
	int clientSocket;
	struct sockaddr_in client;
	socklen_t clientSize;
	
	char buff[1024];
	pid_t childPid;
	char server_message[256] ="you have reached the server";

	serverSocket= socket(AF_INET, SOCK_STREAM,0);
	if (serverSocket==-1) {
		perror("error creating server socket");
	}
	printf("%s\n", "server socket created successfully !");
	
	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	server.sin_addr.s_addr = INADDR_ANY;

	bindStatus = bind(serverSocket,(struct sockaddr*)&server, sizeof(server));
	if(bindStatus==-1){
	      perror("binding error !");	
	      close(serverSocket);
	      exit(1);
	}
	printf("%s\n", "server binded succesfully!");
	if (listen(serverSocket,5)==0) {
	      printf("%s\n", "server listening... ");	
	}	
	while (1==1) {
	clientSocket = accept( serverSocket,(struct sockaddr *)&client,&clientSize);
	if (clientSocket == -1 ) {
		perror("conection failed ");
		exit(1);
	}
	printf("conection accepted from %s:%d your are client %d \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),clientSocket);
	if ((childPid =fork())==0) {
	      close(serverSocket);
	      while(1){
		   
		   recv(clientSocket,buff,sizeof(buff),0);
		   if(strcmp(buff,":exit")==0){
			 printf("%s:%d disconnected \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
			 break;
		   }else{
			printf("client :%s\n", buff);
		//	memset(buff,0,sizeof(buff));	
		//	scanf("%[^\n]",buff);
			send(clientSocket,buff,sizeof(buff),0);
			memset(buff,0,sizeof(buff));	
		   }
	      } //1
	} //child
	}// 1==1

	close(clientSocket);
	return 0;
}
