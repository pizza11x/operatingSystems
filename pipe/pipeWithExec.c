#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 1024

int main(int argc, char** argv){
    int pfd[2], pid;
    if(pipe(pfd) == -1){
        perror("Pipe function failed!\n");
        exit(-1);
    }
    if((pid = fork()) < 0){
        perror("Fork function failed!\n");
        exit(-2);
    }
    if(pid == 0){ //Child
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp("wc", "wc", "-w", NULL);
        perror("wc failed!\n");
        exit(-3);
    }else{ //Parent
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        execlp("ls", "ls", NULL);
        perror("ls failed!\n");
        exit(-4);
    }


    return 0;
}