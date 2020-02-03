// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <pthread.h>
#include <netinet/in.h> 

#define PORT	 5030
#define MAXLINE 1024

char* wait_new_client = "\nWaiting for Client\n";


char buffer[MAXLINE];
int Index=0;


struct Data
{
	int NewFD;
	int ClientPort;
	char* ClientIP;
	char UserName[50];
};

struct Data ClientList[50];

void * Broadcast_Message(void * ptr){

	struct Data *ClientInfo = (struct Data *)ptr;
	int port=ClientInfo->ClientPort;
	char buf[1024];
	strcpy(buf,buffer);
	send(ClientInfo->NewFD, (const char *)buf, strlen(buf), 0); 
}

void* Communication(void* Info)
{
	struct Data *ClientInfo = (struct Data *)Info;
	send(ClientInfo->NewFD,"Enter Your Name",strlen("Enter Your Name"),0);
	char name[50];
	int n=recv(ClientInfo->NewFD,name,50,0);
	name[n]='\0';
	char pt[10];
	sprintf(pt,"%d",ClientInfo->ClientPort);
	strcat(name,pt);
	strcpy(ClientInfo->UserName,name);
	sprintf(name,"Your User Name is : %s",ClientInfo->UserName);
	send(ClientInfo->NewFD,(const char*)name,strlen(name),0);
	while(1){
		memset(&buffer, 0, sizeof(buffer)); 
		 n = recv(ClientInfo->NewFD, buffer, MAXLINE, 0);
		buffer[n] = '\0';
		char buffer1[1024];
		if(strcmp(buffer, "exit") == 0){

			for(int i = 0; i < Index; i++){

				if(ClientList[i].NewFD == ClientInfo->NewFD){
					close(ClientList[i].NewFD);
					ClientList[i].NewFD = -1;
					break;
				}

			}
			
			break;
		}
		else if(strcmp(buffer,"online")==0)
		{
		send(ClientInfo->NewFD,"*************** Online User's *****************\n\n",strlen("*************** Online User's *****************\n\n"),0);
		sleep(1);	
			for(int i = 0; i < Index; i++){
					
					if(ClientList[i].NewFD != ClientInfo->NewFD)
					{
					send(ClientInfo->NewFD,(const void*)ClientList[i].UserName,strlen(ClientList[i].UserName),0);
					sleep(1);
					}	

			}
		send(ClientInfo->NewFD,"\n\n****************************************\n\n",strlen("\n\n****************************************\n\n"),0);		
		}
		else
		{

			char *msg;
			msg=strtok(buffer,":");
			char *substr=msg;
			char buf1[100];
			 msg = strtok(NULL, ":");
			//printf("%s",msg);
			//write(1,msg,strlen(msg));
			for(int i = 0; i < Index; i++){

				if(ClientList[i].NewFD != -1 && strcmp(ClientList[i].UserName,substr)==0){
					
					sprintf(buffer1,">> %s : %s",ClientInfo->UserName,msg);
		
					strcpy(buffer,buffer1);
					send(ClientList[i].NewFD,buffer,strlen(buffer),0);
					break;
				}

			}
		}

	}

	
	
}

int main() { 
	int sockfd;
	struct sockaddr_in servaddr, cliaddr; 
	int new_sockfd;
	pthread_t tid;
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	listen(sockfd,5);	// set a backlog for server

	while(1)
	{
		int len, n; 
		write(1,wait_new_client,strlen(wait_new_client));
		int clientLength = sizeof(cliaddr);
		new_sockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clientLength);	// accept request from TCP client		
		int port = ntohs(cliaddr.sin_port);
		char* cIP = inet_ntoa(cliaddr.sin_addr);
		
		char buf[100];

		sprintf(buf, "New Client connected with IP %s and Port %d", cIP, port);

		for(int i = 0; i < Index; i++){

			send(ClientList[i].NewFD, buf, strlen(buf), 0);

		}

		
		ClientList[Index].NewFD = new_sockfd;
		ClientList[Index].ClientPort = port;
		ClientList[Index].ClientIP = cIP;
		
		pthread_create(&tid,NULL,Communication,(void*)&ClientList[Index]);

		Index++;
	}
	
	pthread_exit(NULL);
	return 0; 
} 

