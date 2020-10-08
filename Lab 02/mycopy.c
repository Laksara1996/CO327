#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int in, out;
	size_t size = 100;
	int ret;

	in = open(argv[1], O_RDONLY);
	
	if(in == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	}

	char* buffer = (char *) calloc(100, sizeof(char)); /* size of a char is 1. This buffer holds the read back value. */

	ret = read(in,buffer,1000);

	if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}

	buffer[ret] = '\0'; /* we have to null terminate the string ourselves. */
	
	ret = close(in);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	out = open(argv[2], O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR ); /*second parameter is a flag and third a mode. Find out what they do */
	
	if(out == -1)
	{
		/* the exact error could be found out by looking at the variable errno. We do not cover it here */
		fprintf(stderr,"Couldn't open the file for writing\n");
		return 1;
	}

	ret = write(out,buffer,strlen(buffer));
	
	if(ret == -1)
	{
		fprintf(stderr,"Error writing to file\n");
		return 1;
	}
	
	free(buffer);

	ret = close(out);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	return 0;
}
