#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int pid, fd[2];
    pipe(fd);
    if((pid = fork()) == 0){
        close(fd[0]);
        //Redirect stdout to pipe
        dup2(fd[1], 1);
        execlp("ls", "ls", NULL);
        close(fd[1]);
    }else if(pid > 0){
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("sort", "sort", NULL);
        close(fd[0]);
    }


    return 0;
}