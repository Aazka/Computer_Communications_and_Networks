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

//char *hello = "File1.txt,File2.txt"; 
int PORT = 1234;

#define MAXLINE 1024
char buffer[MAXLINE]; 
char buffer2[MAXLINE];
struct Data
{
	int fd;
	char *hello;
	//char *hello;
};
void *thread_communication(void* ptr)
{
	int n;
	struct Data* D=(struct Data*) ptr;
	while(1){
	n=recv(D->fd,(char *)buffer,MAXLINE,0);
	buffer[n]='\0';
	if(strcmp(buffer,"exit")==0)
	{

		printf("serverSocketClose");
		close(D->fd);
		//pthread_exit(NULL);
		break;
	}
	printf("Server receive%s\n",buffer);
	send(D->fd,(char*)buffer2,MAXLINE,0);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	//pthread_t tid;
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
//	while(1){
		pthread_t tid;
		int len = sizeof(cliaddr);
		int newfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
		abc->fd=newfd;
		int thread=pthread_create(&tid,NULL,thread_communication,(void*)abc);
		pthread_join(tid,NULL);
		if(thread<0)
		{
			printf("pthread Not create\n");
		}
		//pthread_join(tid,NULL);
//	}
	
	return 0;
}