#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

const char banner [] = "hello there\n";

int main()
{
	int pipe_ptoc[2];
	int pipe_ctop[2];
	pid_t pid;

	if(pipe(pipe_ptoc)) 
	{
		perror("Pipe creation");
		
		return -1;
	}
	if(pipe(pipe_ctop)) 
	{
		perror("Pipe creation");
		return -1;
	}


	pid = fork();
	if(pid < 0) 
	{
		perror("Fork");
		return -1;
	}

	if(pid > 0) 
	{ /* parent */
		close(pipe_ptoc[0]);
		close(pipe_ctop[1]);

		int count;

		char buffer[100];

		printf("Enter the string: ");
		scanf("%s",buffer);

		write(pipe_ptoc[1], buffer, strlen(buffer));

		count = read(pipe_ctop[0], buffer, 100);

		buffer[count] = '\0';

		printf("%s\n",buffer);
	}
	if(pid == 0) 
	{ /* child */
		char buff[100];

		close(pipe_ptoc[1]);
		close(pipe_ctop[0]);

		int count;

		while(1) {
			count = read(pipe_ptoc[0], buff, 128);
			for(int i = 0; i < count; i++){
				buff[i] = buff[i] - 32;
			}
			write(pipe_ctop[1], buff, count);
		}
	}
	return 0;
}
