// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int PORT = 1234;
#define MAXLINE 1024

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from AAzka"; 
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
	servaddr.sin_addr.s_addr = inet_addr("172.28.4.36"); 
	

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	int n=recv(sockfd,(char*)buffer,MAXLINE,0);
	buffer[n]='\0';
	printf("%s\n",buffer);
	
	send(sockfd,(char *)hello,strlen(hello),0);
	//do send recv here
	
	close(sockfd); 
	return 0; 
} 