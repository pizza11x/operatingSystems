#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
    void (*oldHandler) (int); 
    printf("I can be stopped!\n");
    sleep(3);
    oldHandler = signal(SIGINT, SIG_IGN);
    printf("I'm protect by CTRL-C\n");
    sleep(3);
    signal(SIGINT, oldHandler);
    printf("I can be stopped again!n\n");
    sleep(3);
    printf("Hi!\n");
    
    return 0;
}