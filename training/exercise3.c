#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int status;
    pid_t childPid;
    printf("----- START -----\n");
    //Child
    if((childPid = fork())== 0){
        execl("/bin/ls", "ls", "-l", NULL);
        printf("CHILD: This should not be executed\n");
    }else{ //Parent
        printf("PARENT: Waiting...\n");
        waitpid(childPid, NULL, 0);
        printf("New child\n");
        if((childPid = fork()) == 0){
            sleep(5);
            printf("CHILD: Hello World!\n");
            exit(0);
        }else{
            printf("PARENT: I'm waiting for the child\n");
            waitpid(childPid, NULL, 0);
            printf("PARENT: Child has finished\n");
        }
    }

    printf("\n----- END -----\n");
    exit(0);
}