#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char **argv){
    sem_t *sem;
    int val;
    if(argc != 2){
        fprintf(stderr, "usage semGetValue <name>");
        exit(-1);
    }
    sem = sem_open(argv[1], 0);
    sem_getvalue(sem, &val);
    printf("value = %d\n", val);

    return 0;
}