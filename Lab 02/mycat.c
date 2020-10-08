#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
	int out;
	size_t size = 100;
	size_t ret;

	out = open("sample.txt", O_RDONLY);
	
	if(out == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	}

	char* buffer = malloc(size+1); /* size of a char is 1. This buffer holds the read back value. */

	ret = read(out,buffer,size);

	if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
	buffer[ret] = '\0'; /* we have to null terminate the string ourselves. */
	
	printf("%s",buffer);
	/* In case there was something already written in the file, the text read back might not be the same as what was written */
	
	
	free(buffer);

	ret = close(out);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	return 0;
}
