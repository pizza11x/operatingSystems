#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(int argc, char ** argv){
    int fd[2];
    pipe(fd); //Create anonymous pipe
    if(fork() != 0){ //Parent writer
        close(fd[READ]);
        dup2(fd[WRITE], 1);
        close(fd[WRITE]);
        execlp(argv[1], argv[1], NULL);
        perror("Connect failed!\n");
        exit(-1);
    }else{ //Child reader
        close(fd[WRITE]);
        dup2(fd[READ], 0);
        close(fd[READ]);
        execlp(argv[2], argv[2], NULL);
        perror("Connect failed!\n");
        exit(-1)
    }

    return 0;
}