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
struct Data
{
	char *ip;
	int port;
};
int main(int argc, char *argv[]){

	struct Data D[100];
    int size = 0;
	int sockfd; 
	char buffer[MAXLINE]; 
	char buffer2[MAXLINE];
	char *hello = "message recive"; 
	struct sockaddr_in	 servaddr, cliaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 

	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	int len,n;
	int i=0;
	while(i<10){
		len = sizeof(cliaddr);
		//recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		n=recvfrom(sockfd,(char *)buffer,MAXLINE,MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
		buffer[n]='\0';
		printf("%s\n",buffer);
		D[i].ip=malloc(12*sizeof(char));
		D[i].ip=inet_ntoa(cliaddr.sin_addr);
		D[i].port=ntohs(cliaddr.sin_port);
		if(i==0)
		{
			sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);	
		}
		else
		{
			for(int j=0;j<i;j++)
			{
		//		printf("%d\n",j);
				sprintf(buffer,"client %d IP %s Port %d\n",j,D[j].ip,D[j].port);
				strcat(buffer2,buffer);
			}
		//	printf("%s\n",buffer);
			sendto(sockfd, (const char *)buffer2, strlen(buffer2), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);				
		}
		//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		i++;
	}
	close(sockfd); 
	return 0;
}
