#include "./apue.h"
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% "); //emulate prompt - printf required "%%"" to print "%"
    while(fgets(buf, MAXLINE, stdin) != NULL){
        buf[strlen(buf) - 1] = 0; //replace newline with NULL
        if((pid = fork()) < 0){
            err_sys("Fork error");
        }
        else if(pid == 0){ //child
            execlp(buf, buf, (char *)0);
            err_ret("Couldn't execute : %s", buf);
        }
        if((pid = waitpid(pid, &status, 0)) <0){
            err_sys("Waitpid error");
            printf("%% ");
        }

    }

    exit(0);

}