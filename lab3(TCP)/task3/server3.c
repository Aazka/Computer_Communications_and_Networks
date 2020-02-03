// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "File1.txt,File2.txt"; 
	char hello2[MAXLINE];
	struct sockaddr_in servaddr, cliaddr; 
	
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
	//Listen
	int listens=listen(sockfd,10);
	if(listens<0)
	{
		perror("Listen failed"); 
		exit(EXIT_FAILURE);	
	}
	while(1){
	//acceptence
	int clilen=sizeof(cliaddr);
	int newFD=accept(sockfd, (struct sockaddr *)&cliaddr,&clilen);
	//printf("File1.txt,File2.txt");
	if(newFD<0)
	{
		perror("acceptence failed"); 
		exit(EXIT_FAILURE);	
	}
	send(newFD,(char *)hello,strlen(hello),0);
	int len, n; 
	n=recv(newFD,(char *)buffer, MAXLINE,0);
	
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
	buffer[n] = '\0';
	printf("%s\n",buffer);
	FILE *fptr=fopen(buffer,"r"); 
	fscanf(fptr,"%s",hello2);
	//printf("Client : %s\n", buffer); 
	//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
	send(newFD,(char *)hello2,strlen(hello2),0);
	printf("%s\n",hello2); 
	}
	return 0; 
} 

