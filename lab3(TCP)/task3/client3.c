// Client side implementation of UDP client-server model 
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
	char *hello; 
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
	
	//CONNECCT
	int connection=connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(connection<0)
	{
		perror("connection failed"); 
		exit(EXIT_FAILURE);	
	}
	int n, len; 
	n=recv(sockfd, (char *)buffer,MAXLINE,0);
	buffer[n] = '\0'; 
	printf("%s\n",buffer);
	scanf("%s",hello);	
	hello[strlen(hello)] = '\0';
	//sending
	send(sockfd, (const char *)hello, strlen(hello),0);
	//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	printf("%s is send\n",hello); 
	n=recv(sockfd,(char *)buffer,MAXLINE,0);	
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	buffer[n] = '\0'; 
	printf("%s\n", buffer); 
	
	
	close(sockfd); 
	return 0; 
} 

