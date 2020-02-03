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
	char *hello="Hello";
	char input[100];

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
	
	//do send recv here
	send(sockfd,(char *)hello,strlen(hello),0);

	int n=0;
	char op[1];
	while(1){
		printf("im am a while loop\n");
		//menu Recive
	n=recv(sockfd,(char *)buffer,MAXLINE,0);
	buffer[n]='\0';
	printf("%s Client\n",buffer);
	//entering File name
	scanf("%[^\n]",input);
	//sending file name
	if(send(sockfd,(char *)input,strlen(input),0)==-1)
	{
		printf("Error.......!");
	    exit(1);	
	}
	//recive faile data
	n=recv(sockfd,(char*)buffer,MAXLINE,0);
	buffer[n]='\0';
	FILE *fptr;
	fptr = fopen("program.txt", "w");
	if(fptr == NULL)
	{
		printf("Error!");
	    exit(1);
	}
	//write it in file
	fprintf(fptr,"%s", buffer);
	printf("%s\n",buffer);
	//reciving option msg
	
	n=recv(sockfd,(char*)buffer,MAXLINE,0);
	buffer[n]='\0';
	printf("%s\n",buffer);
	scanf("%s",op);
	//
	printf("%s\n",op);
	//strcpy(op,"N");
	if(send(sockfd,(char*) op,1,0)==-1)
	{
		printf("Error!");
	    exit(1);
	}
	if(op[0]=='n' ||op[0]=='N')
	{
		printf("HELLOOOOOO\n");
		close(sockfd); 
		return 0;
	}
	}	
	return 0; 
} 