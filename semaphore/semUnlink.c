#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "usage: semUnlink <name>\n");
        exit(-1);
    }
    sem_unlink(argv[1]);

    return 0;
}