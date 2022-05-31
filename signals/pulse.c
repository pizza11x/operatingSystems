#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
    int pid1, pid2;
    pid1 = fork();
    if( pid1 == 0){
        while(1){
            printf("pid1 is alive..\n");
            sleep(1);
        }
    }
    pid2 = fork();
    if(pid2 == 0){
        while(1){
            printf("pid2 is alive..\n");
            sleep(1);
        }
    }
    sleep(2);
    kill(pid1, SIGSTOP);
    printf("pid1 is stopped!\n");
    sleep(2);
    kill(pid1, SIGCONT);
    printf("pid1 is alive again..\n");
    sleep(2);
    kill(pid1, SIGINT);
    printf("pid1 is stopped!\n");
    kill(pid2, SIGINT);
    printf("pid2 is stopped!\n");


    return 0;
}