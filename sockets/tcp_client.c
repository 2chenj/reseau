#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <string.h>
int main(int argc, char *argv[])
{
      //socket
      //connect
	  //create the server addr to connect to
	  //conect 
      //recev
	//varibale to hold data received
	//print out the data
      //close
        
	// try to convert the IP adresss  as a string to int then to s_addr_t type
	unsigned int  a,b,c,d,base10ClientIP;
	int clientPort = atoi(argv[2]);
	char *clientIP = argv[1];
	a = atoi(strtok(clientIP,"."));
	b = atoi(strtok(NULL,"."));
	c = atoi(strtok(NULL,"."));
	d = atoi(strtok(NULL,"."));
	
	a *= 16777216;
	b *= 65536;
	c *= 256;
	base10ClientIP = a+b+c+d;
	
	printf("%u\n", base10ClientIP);

	int clientSocket,connectionStatus;
	struct sockaddr_in server;
	char buff [1024];	

        clientSocket = socket(AF_INET,SOCK_STREAM,0);
	if (clientSocket ==-1) {
		perror(" error creating the socket");
		exit(1);
	}
	printf("%s\n", "client socket created successfully !");

	memset(&server,'\0',sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(clientPort);	
	server.sin_addr.s_addr =INADDR_ANY ;

	connectionStatus = connect(clientSocket,(struct sockaddr *) &server,sizeof(server));
	if (connectionStatus ==-1) {
		printf("there was an error when trying to connect to server \n");
		exit(1);
	}
	printf("%s\n", "connection succes !" );	
	while(1){
		scanf("%[^\n]%*c",&buff[0]);
		send(clientSocket,&buff, sizeof(buff),0);
		if (strcmp(buff,":exit")==0) {
		      close(clientSocket);
		      printf("%s\n", "Disconnected from the server.");
		      exit(1);
		}
		//memset(buff,'\0',sizeof(buff));
		if(recv(clientSocket,buff, sizeof(buff),0) <0){
			perror("error receiving data from server");
		}else{
			printf("server : %s\n",buff );
			//memset(buff,0,sizeof(buff));
		}
	}	
	return 0;
}
