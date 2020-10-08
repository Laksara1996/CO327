#include <fcntl.h> 
#include <stdio.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024 

int main() 
{ 
    int fd,fdd; 
    char* fifoSimple = "/tmp/fifoSimple";
    char* fifoCapital = "/tmp/fifoCapital";

    mkfifo(fifoSimple,0666);
    mkfifo(fifoCapital,0666);

    fd = open(fifoSimple, O_RDONLY); 
    dup2(fd, fileno(stdin));
    fd = open(fifoCapital, O_WRONLY); 
    dup2(fd, fileno(stdout));

    char *tr_args[] = {"tr", "[:lower:]","[:upper:]", NULL};

    execvp(tr_args[0], tr_args);

    close(fd); 
    close(fdd); 

    return 0; 
}
