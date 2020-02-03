#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

//This is an incomplete code for a UDPO

int PORT = 1234;
#define MAXLINE 1024
int main(int argc, char *argv[]){

	int sockfd; 
	char buffer[MAXLINE];
	//har hello="hello form server";
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

		perror("\nIssue in Server!!! not Binded!\n");
		exit(-1);

	}
	listen(sockfd, 10);
	int len=sizeof(cliaddr);
	//send(sockfd, (const char *)hello, strlen(hello),0);
	while(1){
		
		int Newfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		int n=recv(Newfd, (char *)buffer, MAXLINE, 0);
		buffer[n] = '\0';
		write(1,buffer,strlen(buffer));
		//printf("%s\n", buffer);

		char *p=strtok(buffer," ");
		mkdir(p,0777);

		while(1){
		char *ptr=strtok(NULL,",");
		if(ptr==NULL)
		{
			break;
		}
		else if(strstr(ptr,".txt")==NULL)
		{
			char ptr2[MAXLINE];
			sprintf(ptr2,"%s/%s",p,ptr);
			mkdir(ptr2,0777);	
		}	
		else{
			char ptr2[MAXLINE];
			sprintf(ptr2,"%s/%s",p,ptr);
			FILE *fptr=fopen(ptr2,"w");
			fclose(fptr);
		
		}	
	}
		close(sockfd);
	}

	return 0;
}