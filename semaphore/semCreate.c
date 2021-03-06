#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


#define FILE_MODE S_IRUSR|S_IWUSR
 
int main(int argc, char **argv){
    int c, flags;
    sem_t *sem;
    unsigned int value;
    flags = O_CREAT;
    value = 1;
    while( (c = getopt(argc, argv, "ei:")) != -1){
        switch (c){
        case 'e':
            flags |= O_EXCL;
            break;
        case 'i':
            value= atoi(optarg);
            break;
        }
    }
    if(optind != argc -1){
        fprintf(stderr, "usage: semcreate [-e] [-i initialValue] <name>\n");
        exit(-1);
    }
    sem = sem_open(argv[optind], flags, FILE_MODE, value);
    sem_close(sem);
    
    return 0;
    
}