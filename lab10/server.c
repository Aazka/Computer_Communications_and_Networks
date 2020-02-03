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
	char buffer2[MAXLINE];
	//char hello="Enter any two number";
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
	sprintf(buffer,"Hi \n Enter Two number or Type Exit\n");
	//send(sockfd, (const char *)hello, strlen(hello),0);
	while(1){
		
		int Newfd=accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		/*send(Newfd,"Hi",2,0);
		sleep(2);*/
		
		while(1){
		send(Newfd, (const char *)buffer, strlen(buffer),0);
		int n=recv(Newfd, (char *)buffer2, MAXLINE, 0);
		buffer2[n] = '\0';
		printf("%s\n",buffer2 );
		
		if(strcmp(buffer2,"Exit")==0)
		{
			write(1,"serverSockClose",20);
			close(Newfd);	
			break;	
		}
		int num1=atoi(strtok(buffer2,","));
		int num2=atoi(strtok(NULL,","));
		
		char buffer3[MAXLINE];
		int sum=num1+num2;
		int mul=num1*num2;
		int div=num1/num2;
		int sub=num1-num2;

		sprintf(buffer3,"Sum: %d+%d=%d\n Mul:%d*%d=%d\n, Div:%d/%d=%d\n, sub:%d-%d=%d\n",num1,num2,sum,num1,num2,mul,num1,num2,div,num1,num2,sub);
		send(Newfd, (const char *)buffer3, strlen(buffer3),0);
		}
	}
		
	return 0;
}
