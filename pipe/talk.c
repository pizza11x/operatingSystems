#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

char *string = "Message...";

int main(void){
    int fd[2], bytesRead;
    char message[100];

    pipe(fd);
    if(fork() == 0){
        close(fd[READ]);
        write(fd[WRITE], string, strlen(string)+1);
        close(fd[WRITE]);
    }else{
        close(fd[WRITE]);
        bytesRead=read(fd[READ], message, 100);
        printf("Read %d byte; %s\n", bytesRead, message);
        close(fd[READ]);
    }


    return 0;
}