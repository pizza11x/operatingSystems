#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct twoInt{ int a, b; } data;
void signalHandler(int signalNo);

int main(){

    static struct twoInt zero = {0,0}, uno = {1,1};
    signal(SIGALRM, signalHandler);
    data = zero;
    alarm(1);
    while(1){
        data = zero;
        data = uno;
    }
    
}

void signalHandler(int signalNo){
    printf("%d %d\n", data.a, data.b);
    alarm(1);
}