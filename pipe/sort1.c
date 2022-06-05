#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    int fds[2];
    pid_t pid;
    //Create pipe.
    pipe(fds);
    //Create child process
    pid = fork();
    if( pid == (pid_t) 0){
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        //replace the child process with the sort command
        execlp("sort", "sort", 0);
        close(fds[0]);
    }else{
        close(fds[0]);
        write(fds[1], "This is a test.\n", 16);
        write(fds[1], "Hello, world.\n", 14);
        write(fds[1], "My dog had fleas.\n", 18);
        write(fds[1], "This program is great.\n", 23);
        write(fds[1], "One fish, two fish.\n", 20);
        close(fds[1]);
        //Wait child process 
        waitpid(pid, NULL, 0);
    }


    return 0;
}