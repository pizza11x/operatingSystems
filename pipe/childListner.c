#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SIZE 1024

int main(void){
    int pfd[2];
    int nread;
    int pid;
    char buf[SIZE];
    if(pipe(pfd) == -1){
        perror("pipe() error!");
    }
    if((pid = fork())< 0){
        perror("fork() fallita!");
        exit(-2);
    }
    if(pid == 0){ //CHILD
        close(pfd[1]);
        while((nread = read(pfd[0], buf, SIZE) != 0))
            printf("Child reads: %s\n",buf);
        close(pfd[0]);
    }else{
        close(pfd[0]);
        strcpy(buf, "Sono tuo padre!");
        write(pfd[1], buf, strlen(buf)+1);
        close(pfd[1]);
    }

    return 0;
}