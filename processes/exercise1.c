#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    pid_t pid;
    int status;

    if((pid = fork()) < 0){
        perror("Fork error!");
        exit(-1);
    }
    //CHILD
    if(pid == 0){
        exit(0);
    }
    //PARENT
    //Time to observe the zombie using ps
    sleep(60);
    //Parent waits its child's
    pid = wait(&status);
    if(WIFEXITED(status)){
        fprintf(stderr, "\n\t%d\tProcess %d exited with status %d. \n", 
            (int) getpid(), pid, WEXITSTATUS(status));
    }

    exit(0);
}