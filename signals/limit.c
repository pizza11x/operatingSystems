#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int delay;
void childHandler(int);

int main(int argc, char *argv[]){
    int pid;
    signal(SIGCHLD, childHandler);
    pid = fork();
    if(pid == 0){
        execvp(argv[2], &argv[2]);
    }else{
        sscanf(argv[1], "%d", &delay);
        sleep(delay);
        printf("Child %d exceeded limit and is being killed!\n", pid);
        kill(pid, SIGINT);
    }


    return 0;
}

void childHandler(int signalNo){
    int childPid, childStat;
    childPid = wait(&childStat);
    printf("Child %d terminated within %d seconds\n", childPid, delay);
    exit(0);
}