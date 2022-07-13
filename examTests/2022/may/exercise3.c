#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int result1, result2;

void handler(int sig){
    if(sig == SIGUSR1){
        result1 = getpid() + getppid();
        printf("The result 1 is: %d\n", result1);
    }else if( sig == SIGUSR2){
        result2 = getppid() - getpid();
        printf("The result 2 is: %d\n", result2);
    }else{
        printf("TEST");
    }
}

int main(int argc, char** argv){
    int input;
    pid_t child1, child2;

    if(argc < 2){
        printf("Usage: %s number (1-1000)\n", argv[0]);
        exit(-1);
    }

    input = atoi(argv[1]);

    if(input < 1 || input > 1000){
        printf("The number value must be between 1 and 1000\n");
        exit(-1);
    }
    if((child1 = fork()) == 0){ //Child1
        if((input %2) == 0){
            signal(SIGUSR1, handler);
            pause();

        }else{
            printf("I'm the first child %d\n", getpid());
        }
    }else{
        if((child2 = fork()) == 0){ //Child2
            if((input %2) != 0){
                signal(SIGUSR2, handler);
                pause();
            }else{
                printf("I'm the second child %d\n", getpid());
            }
        }else{ //Parent
            if(waitpid(child1, NULL, 0) < 0){
                perror("Wait Error!"); 
                exit(-1);
            }
            if(waitpid(child2, NULL, 0) < 0){
                perror("Wait Error!"); 
                exit(-1);
            }
            printf("pidChild1 * pidChild2 = %e\n", (child1*child2));
            printf("Hi from the parent!\n");
        }
    }

    if(child1 < 0 || child2 < 0){
        printf("Fork error!\n");
        exit(-1);
    }


    return 0;
}