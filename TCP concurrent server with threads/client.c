// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <pthread.h>
#include <netinet/in.h> 

#define PORT	 5030
#define MAXLINE 1024 


void * SEND_HANDLER(void * sendd){

	int newfd = *((int *)sendd);	
	char buf[100];
	while(1){
		
		memset(buf, '\0', 100);
		scanf("%[^\n]%*c", buf);
		send(newfd, buf, strlen(buf), 0);

		if(strcmp(buf, "exit") == 0){
			
			close(newfd);
			break;	
		}
	}
}


void * RECEIVE_HANDLER(void * receive){

	int newfd = *((int *)receive);	
	char buf[1024];
	while(1){
		
		memset(buf, '\0', 100);
		int n = recv(newfd, buf, 1024, 0);
		buf[n] = '\0';
		printf("%s\n", buf);

		if(n <= 0){
	
			break;		
		
		}

	}


}

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from client"; 
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

	int n, len; 
	pthread_t tid;
	
	pthread_create(&tid, NULL, SEND_HANDLER, (void *)&sockfd);
	pthread_create(&tid, NULL, RECEIVE_HANDLER, (void *)&sockfd);
		
	
	pthread_exit(NULL);
	
	close(sockfd); 
	return 0; 
} 

