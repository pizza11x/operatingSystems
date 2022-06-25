/*
    I used named semaphores instead of in-memory semaphores 
    because on Mac Os in-memory semaphores are not supported.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define N 5
#define SEM_FULL "/full"
#define SEM_MUTEX "/mutex"

const char* SEM_THREADS[5]={ "/thread1", "/thread2", "/thread3", "/thread4", "/thread5"};

struct threadStruct{
    int sleepTime;
    int index;
    pthread_t tid;
};

struct {
    sem_t *full;
    sem_t *semThreads[N];
    sem_t *mutex;
    int allWaiting;
    int queue[N];
    char semNameThreads[N];
} shared;

void unlinkSem();

void *funThread(void *args){
    struct threadStruct *t_arg = (struct threadStruct *)args;
    sleep(t_arg->sleepTime);
    printf("Thread #%d woke up!\n", t_arg->index);

    sem_wait(shared.mutex);
        shared.queue[shared.allWaiting] = t_arg->index-1;
        shared.allWaiting++;
        if(shared.allWaiting == 5){
            sem_post(shared.full);
        }
    sem_post(shared.mutex);
    sem_wait(shared.semThreads[t_arg->index-1]);
    printf("Thread #%d termianted!\n", t_arg->index);

    return NULL;
}

int main(int argc, char** argv){

    struct threadStruct threads[N];
    shared.allWaiting = 0;
    


    if(argc < 6){
        printf("Usage: %s 5 6 7 8 9\n",argv[0]);
        printf("The 5 numbers printed are only for dimonstration!\n");
        exit(-1);
    }
    
    unlinkSem();
    for(int k = 0; k<N; k++){
        if(atoi(argv[k+1]) <= 5 || atoi(argv[k+1]) >= 20){
            printf("The value of the numbers must be between 5 and 20!\n");
            exit(-1);
        }else{
            threads[k].sleepTime = atoi(argv[k+1]);
            threads[k].index = k+1;
            shared.semThreads[k] = sem_open(SEM_THREADS[k], O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
        }
    }
    shared.full = sem_open(SEM_FULL, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
    shared.mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);

    for(int i = 0; i<N; i++){
        if(pthread_create(&threads[i].tid, NULL, *funThread, (void *)&threads[i]) != 0){
            printf("Thread creation error!\n");
            exit(-1);
        }
    }

    sem_wait(shared.full);

    for(int z=0; z<N; z++){
        sem_post(shared.semThreads[shared.queue[z]]);
        sem_close(shared.semThreads[shared.queue[z]]);
    }

    for(int j=0; j<N; j++){
        if(pthread_join(threads[j].tid, NULL) != 0){
            printf("Thread join error!\n");
            exit(-1);
        }
    }

    sem_close(shared.mutex);
    sem_close(shared.full);
    return 0;
}

void unlinkSem(){
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_THREADS[0]);
    sem_unlink(SEM_THREADS[1]);
    sem_unlink(SEM_THREADS[2]);
    sem_unlink(SEM_THREADS[3]);
    sem_unlink(SEM_THREADS[4]);

}