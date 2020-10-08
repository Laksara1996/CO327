#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define PORT 12345

void handle_client(int new_socket){


	char buffer[1024];
	
	int valread = read(new_socket, buffer, 1024);
	printf("%s\n",buffer );

	send(new_socket, "hello", strlen("hello"), 0);
	printf("sent");
}

int main(char argc, char **argv){


	struct sockaddr_in cli_addr;

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = INADDR_ANY;
	cli_addr.sin_port = htons(PORT);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bind(sockfd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
	listen(sockfd, 5);

	int clilen = sizeof(cli_addr);


	while(1){
		int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);

		if(newsockfd < 0){
			perror("ERROR on accept");
			exit(1);
		}
		int pid = fork();

		if(pid<0){
			perror("ERROR on fork");
			exit(1);
		}

		if(pid == 0){
			close(sockfd);
			handle_client(newsockfd);
			exit(0);			
		}else{
			close(newsockfd);
		}
	}

	return 0;
}