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
	char hello[100];//= "Hello from client"; 
	FILE *fptr=fopen("file.txt","r");
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
	if(fptr == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int n, len,i=0; 
    int stringLength=0;
	//while(fscanf(fptr,"%s",hello)!=EOF)
	//{
    fscanf(fptr,"%s",hello);
		stringLength=strlen(hello);
		for(int i=0;i<stringLength;i++){
			if(hello[i] >= 'A' && hello[i] <= 'Z')
			{
				hello[i]+=2;
			}
			else if(hello[i] >= 'a' && hello[i] <= 'z')
			{
				hello[i]+=3;
			}
			else
			{
				hello[i]+=1;	
			}
		}
	//}
	//sending
	send(sockfd, (const char *)hello, strlen(hello),0);
	//sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
	//printf("%s\n",hello); 
	n=recv(sockfd, (char *)buffer,MAXLINE,0);	
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
	buffer[n] = '\0'; 
	printf("Server : %s\n", buffer); 
	
	close(sockfd); 
	return 0; 
} 

