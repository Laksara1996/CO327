#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{ 
    char buffer[100];
    char receive[100];

    printf("Enter the Word: ");
    scanf("%s",buffer);

    int fd,fdd; 
    char * fifoSimple = "/tmp/fifoSimple"; 
    char * fifoCapital = "/tmp/fifoCapital";

    mkfifo(fifoSimple,0666); 
    mkfifo(fifoCapital,0666);

    fd = open(fifoSimple, O_WRONLY); 
    write(fd, buffer,strlen(buffer)); 
    close(fd); 

    fdd = open(fifoCapital, O_RDONLY); 
    read(fdd, receive, 1024); 
    printf("Capitalized Word: %s\n", receive);
    close(fdd); 

    unlink(fifoSimple); 
    unlink(fifoCapital); 

    return 0; 
}

