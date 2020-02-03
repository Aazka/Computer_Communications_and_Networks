// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int PORT = 8080;
#define MAXLINE 1024

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from client"; 
	fd_set readfds;
	int max_sd = 0;
	struct sockaddr_in	 servaddr; 

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
	
	while(1){

		
		FD_ZERO(&readfds); // Clearing the reading list of file/socket descriptors
		FD_SET(sockfd, &readfds); //Adding client socket in list
		FD_SET(STDIN_FILENO, &readfds);
	

		if(max_sd < sockfd)
			max_sd = sockfd;

		if(max_sd < STDIN_FILENO)
			max_sd = STDIN_FILENO;

		select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if(FD_ISSET(sockfd, &readfds)){ //receiving data from server side

           	int n = recv(sockfd, buffer, 1000, 0);
			
			buffer[n] = '\0';

			write(1, buffer, strlen(buffer));
			send(sockfd,"YEs",strlen("yes"),0);

				
		}

		if(FD_ISSET(STDIN_FILENO, &readfds)){ //User input

			scanf("%s", buffer);

			send(sockfd, buffer, strlen(buffer), 0);

		}


	}
	
	close(sockfd); 
	return 0; 















} 

