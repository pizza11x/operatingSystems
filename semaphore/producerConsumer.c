#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N_BUFF 10
#define SEM_MUTEX "/mutex"
#define SEM_N_EMPTY "/nempty"
#define SEM_N_STORED "/nstored"
#define FILE_MODE S_IRUSR|S_IWUSR

int nItems; //Read only for producer and consumer
struct { //data shared for producer and consumer
    int buff[N_BUFF];
    sem_t *mutex, *nEmpty, *nStored;
} shared;

void *produce(void *), *consume(void *);

int main(int argc, char **argv){

    pthread_t tid_produce, tid_consume;
    if(argc != 2){
        printf("usage: producerConsumer <#items>\n");
        exit(-1);
    }
    nItems = atoi(argv[1]);

    //Create 3 semaphores
    shared.mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, FILE_MODE, 1);
    shared.nEmpty = sem_open(SEM_N_EMPTY, O_CREAT | O_EXCL, FILE_MODE, N_BUFF);
    shared.nStored = sem_open(SEM_N_STORED, O_CREAT | O_EXCL, FILE_MODE, 0);
    
    //Create a thread producer ad a thread consumer
    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_produce, NULL, consume, NULL);

    //Wait the two threads
    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    //remove semaphores
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_N_EMPTY);
    sem_unlink(SEM_N_STORED);

    return 0;
}

void *produce(void *arg){
    int i;
    for(i = 0; i < nItems; i++){
        sem_wait(shared.nEmpty);
        //Wait a empty place
        sem_wait(shared.mutex);
        shared.buff[i % N_BUFF] = i;
        //save i in the buffer
        sem_post(shared.mutex);
        sem_post(shared.nStored);
        //another elemen is available
    }
    return (NULL);
}

void *consume(void *arg){
    int i;
    for(i = 0; i < nItems; i++){
        sem_wait(shared.nStored);
        //wait an element
        sem_wait(shared.mutex);
        if(shared.buff[i % N_BUFF] != i){
            printf("buff[%d] = %d\n", i, shared.buff[i%N_BUFF]);
        }
        sem_post(shared.mutex);
        sem_post(shared.nEmpty); //another free place
    }
    return (NULL);
}