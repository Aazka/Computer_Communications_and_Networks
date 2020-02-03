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
int main(int argc, char *argv[]){

    int size = 0;
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
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
	while(1){
		int len = sizeof(cliaddr);
		int newfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
		pid_t pid=fork();
		if(pid<0)
		{
			exit(-1);
		}
		else if(pid==0){
			close(sockfd);
			n=recv(newfd,(char *)buffer,MAXLINE,0);
			buffer[n]='\0';
			printf("Client with port %d %s\n",cliaddr.sin_port,buffer);

			send(newfd,(char *)hello,strlen(hello),0);
			close(newfd);
			exit(1);
		}
		close(newfd);
		//add code here

	}
	
	return 0;
}
