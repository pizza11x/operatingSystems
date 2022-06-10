#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char **argv){
    sem_t *sem;
    int val;
    if(argc != 2){
        fprintf(stderr, "usage: semPost <name>\n");
        exit(-1);
    }
    sem = sem_open(argv[1], 0);
    sem_post(sem);
    sem_getvalue(sem, &val);
    printf("The value is = %d\n", val);

    exit(0);
}