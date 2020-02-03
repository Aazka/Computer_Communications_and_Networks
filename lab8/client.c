#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int PORT = 1234;
#define MAXLINE 1024
int main(int argc, char *argv[]){

	int sockfd; 
	char buffer[MAXLINE];
	int len;
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
	
	connect (sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

	FILE* fptr;
	fptr = fopen("abc.txt", "r");
	char line[MAXLINE]={'\0'};
	fscanf(fptr,"%[^\n]",line);
	 printf("%s",line);
	send(sockfd, line, strlen(line),0);
	fclose(fptr);

	close(sockfd);
	
	return 0;
}