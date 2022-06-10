#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char **argv){
    sem_t *sem;
    int val;

    if(argc != 2){
        fprintf(stderr, "usage: semWait <name>");
        exit(-1);
    }
    sem = sem_open(argv[1], 0);
    sem_wait(sem);
    sem_getvalue(sem, &val);
    fflush(stdout);
    printf("pid %ld has semaphore, value = %d\n", (long) getpid(), val);

    pause(); //blocked until user termination
    return 0;
}