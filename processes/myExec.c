#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

char *env_init[] = {"User = sconosciuto", "PATH = /tmp", NULL};

int main(){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("Fork error!");
        exit(-1);
    }else if( pid == 0){
        /*
         * exec function allow to load another program from the disk
         * l --> List
         * e --> vector parameters
         * p --> clone shell
         */
        if(execle("/Users/wakala/Desktop/exercisesSO/processes/echoall", "echoall", "myArg1", "MY ARG2", (char *)0, env_init) < 0){
            perror("execle error!");
            exit(-1);
        }
    }
    if(waitpid(pid, NULL, 0) < 0){
        perror("Wait Error!"); 
        exit(-1);
    }
    if((pid = fork()) < 0){
        perror("Fork error!");
        exit(-1);
    }else if( pid == 0){
        if(execlp("/Users/wakala/Desktop/exercisesSO/processes/echoall", "echoall", "only 1 arg", (char *)0) < 0 ){
            perror("execlp error!");
            exit(-1);
        }
    }

    exit(0);
}

