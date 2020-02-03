// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <pthread.h>
#include <netinet/in.h> 

int PORT = 1234;
#define MAXLINE 1024

char buffer[MAXLINE]; 
char input[100];
struct ClientData
{
	int fd;
	char*hello;

};
void *ClientRecive(void *ptr)
{
	struct ClientData *D=(struct ClientData*) ptr;
	while(1){
	int n=recv(D->fd,buffer,MAXLINE,0);
	buffer[n]='\0';
		if(n<=0)
		{
			close(D->fd);
			printf("ClientSocketClose");
			pthread_exit(NULL);
			break;
		}
	}
	pthread_exit(NULL);
}

void *clientSend(void *ptr)
{
	struct ClientData *D=(struct ClientData*)ptr;
	while(1)
	{
		printf("Enter Data\n");
		scanf("%s",input);
		if(strcmp(input,"exit")==0)
		{
			//send(sockfd,(char *)input,strlen(input),0);
			send(D->fd,input,MAXLINE,0);
			close(D->fd);
			printf("ClientSocketClose");
			break;
			//pthread_exit(NULL);
		}
		else
		{
			send(D->fd,input,MAXLINE,0);	
			printf("U entered %s\n",input);
		}
	} 
	//close(D->fd);
	pthread_exit(NULL);
}
// Driver code 
int main() { 
	int sockfd; 
	char *hello="Hello";
	char input[100];
	struct ClientData *abc;
	abc=(struct ClientData *)malloc(sizeof(struct ClientData));

	struct sockaddr_in	 servaddr, cliaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	//do send recv here
	//send(sockfd,(char *)hello,strlen(hello),0);
	abc->fd=sockfd;

	int n=0;
	//while(1){
		//menu Recive
		pthread_t tid;
		int thread=pthread_create(&tid,NULL,clientSend,(void*)abc);
		pthread_join(tid,NULL);
		if(thread<0)
		{
			printf("pthread Not create\n");
		}
		thread=pthread_create(&tid,NULL,ClientRecive,(void*)abc);
		pthread_join(tid,NULL);
		if(thread<0)
		{
			printf("pthread Not create\n");
		}
	//}	
	return 0; 
} 