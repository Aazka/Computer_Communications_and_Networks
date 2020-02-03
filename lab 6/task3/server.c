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
int indexs = 0;

struct list
{
	int fd;
	int port;
	char *hello;
	//char *hello;
};

void *thread_communication(void* ptr)
{
	printf("Client %d \t",indexs);
	int n;
	struct list* D=(struct list*) ptr;
	while(1)
	{
		memset(buffer,'\0',MAXLINE);
		n=recv(D->fd,(char *)buffer,MAXLINE,0);
		buffer[n]='\0';
	}
	pthread_exit(NULL);
}

void SendALL(struct list L[])
{
	char buffer[MAXLINE];
	sprintf(buffer,"%s",L[indexs].hello);
	
	for(int i=0;i<indexs;i++)
	{
		
		send(L[i].fd,buffer,MAXLINE,0);
	}
	indexs++;
}


int main(int argc, char *argv[]){

	struct  list List[10];
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
		int n=0;
		pthread_t tid;
		int len = sizeof(cliaddr);

		while(1){
		
		int newfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
		sprintf(buffer, "%d", indexs);
		List[indexs].fd = newfd;
		List[indexs].hello = malloc(sizeof(char)*100);
		sprintf(List[indexs].hello,"Client %d",indexs);

		SendALL(List);
	
		int thread=pthread_create(&tid,NULL,thread_communication,(void*)&List[indexs]);
		if(thread<0)
		{
			printf("pthread Not create\n");
		}
	}
	return 0;
}