#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>

int PORT = 1234;

#define MAXLINE 1024
char buffer[MAXLINE]; 
char buffer2[MAXLINE];
char *choice;
char *Options="Do u wants to continue? Y or N";
struct Data
{
	int Port;
	char *IP;
	int fd;
	char *hello;
	//char *hello;
};
void *thread_communication(void* ptr)
{
	int n;
	choice=malloc(sizeof(char)*2);
	struct Data* D=(struct Data*) ptr;
	n=recv(D->fd,(char *)buffer,MAXLINE,0);
	buffer[n]='\0';
	printf("%s Server\n",buffer);
	
	while(1){
		printf("hello while\n");
	sprintf(buffer2,"%d \n %s \n %s",D->Port,D->IP,D->hello);
	send(D->fd,(char *)buffer2,MAXLINE,0);
	printf("hello while\n");
	n=recv(D->fd,(char *)buffer,MAXLINE,0);
	printf("%s\n",buffer );
	if(n<0)
	{
		printf("Error!");
	    exit(1);
	}
	buffer[n]='\0';
	printf("Server receive file name%s\n",buffer);
	FILE *fptr=fopen(buffer,"r"); 
	fscanf(fptr,"%s",buffer2);
	send(D->fd,(char*)buffer2,MAXLINE,0);

	send(D->fd,(char*)Options,MAXLINE,0);
	if(recv(D->fd,(char *)choice,1,0)<0)
	{
		printf("%c\n",choice[0]);
		perror("recv Failed\n");
		exit(EXIT_FAILURE);
	}

	//printf("%c\n",choice[0] );
	//buffer2[n]='\0';
	if(choice[0]!='y')
	{
		printf("hello while\n");
		close(D->fd);	
		pthread_exit(NULL);
		break;
	}
	}
}

int main(int argc, char *argv[]){

	pthread_t tid;
	struct Data *abc;
	abc=(struct Data *)malloc(sizeof(struct Data));
    int size = 0;
	int sockfd; 
	
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

	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(sockfd, 5);
	//char option;
	int n=0;
	while(1){
		pthread_t tid;
		int len = sizeof(cliaddr);
		int newfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
		abc->Port=ntohs(cliaddr.sin_port);
		abc->IP=inet_ntoa(cliaddr.sin_addr);
		abc->fd=newfd;
		abc->hello="File1.txt,File2.txt";
		int thread=pthread_create(&tid,NULL,thread_communication,(void*)abc);
		if(thread<0)
		{
			printf("pthread Not create\n");
		}
	}
	
	return 0;
}