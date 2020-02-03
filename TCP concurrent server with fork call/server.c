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

	if(bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
		perror("bind() call Failed!!");
		exit(-1);
	}

	listen(sockfd, 5);

	while(1){
		int len = sizeof(cliaddr);
		int newfd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
		//add code here
		int pid=fork();
		
		if(pid == -1){
			perror("fork() call failed!");
			continue;
		}

		if(pid == 0){

			close(sockfd);

			int n = recv(newfd, buffer, MAXLINE, 0);

			buffer[n] = '\0';

			write(1, buffer, strlen(buffer));

			send(newfd, hello, strlen(hello), 0);


			close(newfd);
			exit(1);

			//child process
		}
		else{

			close(newfd);

			//parent process
		}


	}
	
	return 0;
}
