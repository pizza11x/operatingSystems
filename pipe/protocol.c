#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ 0 //Reading end of the pipe
#define WRITE 1 //Writing end of the pipe
char *msg[3] = {"Primo", "Secondo", "Terzo"};

int main(void){
    int fd[2], i, length, bytesRead;
    char buffer[100]; //Buffer for the message
    pipe(fd); // create an anonymous pipe
    if(fork() == 0){ //Child, writer
        close(fd[READ]); //Close unused end
        for(i = 0; i < 3; i++){
            length = strlen(msg[i])+1; // Include \0
            write(fd[WRITE], &length, sizeof(int));
            write(fd[WRITE], msg[i], length);
        }
        close(fd[WRITE]); //Close used end
    }else{ //Parent reader
        close(fd[WRITE]); //Close unused end
        while(read(fd[READ], &length, sizeof(int))){
            bytesRead = read(fd[READ], buffer, length);
            if(bytesRead != length){
                printf("Error!\n");
                exit(1);
            }
            printf("Parent: Letti %d byte: %s\n", bytesRead, buffer);
        }
        close(fd[READ]); //Close used end
    }

    return 0;
}