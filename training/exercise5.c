#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LVL 3

int main(){
    int num_nodi = 0;
    for(int i = 0; i < LVL; i++){
        num_nodi += 3^i;
    }
    pid_t pid[num_nodi+1];
    for(int i = 0; i<LVL; i++){
        //Parent
        if((pid[i] = fork()) > 0){  //1st child created
            if((pid[i+1] = fork()) > 0){ //2nd child created
                sleep(i);
                printf("After having waited %d, I've finished!\n", i);
            }
            if((pid[i+2] = fork()) > 0){ //3th child created
                sleep(i);
                printf("After having waited %d, I've finished!\n", i);

            }


            waitpid(pid[i], NULL, 0);
            waitpid(pid[i+1], NULL, 0);
            waitpid(pid[i+2], NULL, 0);
        }
    }

    exit(0);
}