#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    int pipeFd[2];
    pid_t childPid;

    if(pipe(pipeFd) == -1){
        perror("Erorr in pipe");
        exit(EXIT_FAILURE);
    }

    childPid = fork();
    if(childPid == -1){
        perror("Error in fork");
        exit(EXIT_FAILURE);
    }

    if(childPid == 0){
        dup2(pipeFd[1], STDOUT_FILENO);
        close(pipeFd[0]);

        execlp("ls", "ls", "-lF", NULL);
        
        perror("Error in execlp");
        exit(EXIT_FAILURE);
    }else{
        dup2(pipeFd[0], STDIN_FILENO);
        close(pipeFd[1]);

        execlp("wc", "wc", "-w", NULL);
        
        perror("Error in execlp");
        exit(EXIT_FAILURE);
    }


    return 0;
}