#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define PORT 12345

void handle_client(int new_socket){

	while(1){

		char buffer[1024];
		char *sendBuffer;
		size_t size = 0;
		
		int valread = read(new_socket, buffer, 1024);
		buffer[valread - 1] = '\0';
		printf("%s\n",buffer);

		FILE *fp = fopen(buffer, "r");

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);

		sendBuffer = malloc((size + 1) * sizeof(*buffer));

		fread(sendBuffer, size, 1, fp);

		sendBuffer[size] = '\0';

		printf("%s\n",sendBuffer );
		send(new_socket, sendBuffer, size, 0);
		printf("\nData sent\n");
	}
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
			perror("ERROR on accept\n");
			exit(1);
		}
		int pid = fork();

		if(pid<0){
			perror("ERROR on fork\n");
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