#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//One handler for all signals
static void sigUser(int);

int main(){
    if(signal(SIGUSR1, sigUser) == SIG_ERR){
        perror("Can't catch SIGUSR1");
        exit(1);
    }else if(signal(SIGUSR2, sigUser) == SIG_ERR){
        perror("Can't catch SIGUSR2");
        exit(1);
    }else if(signal(SIGINT, sigUser) == SIG_ERR){
        perror("Can't catch SIGINT");
        exit(1);
    }else if(signal(SIGTSTP, sigUser) == SIG_ERR){
        perror("Can't catch SIGTSTP");
        exit(1);
    }

    while(1){ pause();}
}

//sigNo is number signal
static void sigUser(int signNo){
    if(signNo == SIGUSR1){
        printf("\nReceived SIGUSR1\n");
    }else if(signNo == SIGUSR2){
        printf("\nReceived SIGUSR2\n");
    }else if(signNo == SIGINT){
        //ex. CTRL-C
        printf("\nReceived SIGINT\n");
    }else if(signNo == SIGTSTP){
        //ex. CTRL-Z
        printf("\nReceived SIGTSTP\n");
    }else{
        printf("Received %d Signal\n", signNo);
    }

    return;
}
