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
	char *hello = "Aazka"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	//memset(&clientaddr, 0, sizeof(clientaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

	//connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	int len = sizeof(servaddr);
	sendto(sockfd,(const char *)hello,strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&servaddr, sizeof(servaddr));
	int n=recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
	buffer[n]='\0';
	printf("%s\n",buffer);
	close(sockfd); 
	return 0; 
} 

