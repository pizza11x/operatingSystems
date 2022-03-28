#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    pid_t childPid = 0;
    int i, n;
    if(argc != 2){
        fprintf(stderr, "Uso: %s proocessi\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    for( i = 1; i < n; i++){
        if(childPid = fork()){
            break;
        }
    }
    printf("\n ------------------------------------- \n");
    printf("i: %d\nprocesso ID: %d\npadre ID: %d\nfiglio ID: %d\n",
            i, getpid(), getppid(), childPid);
    
    exit(0);
}