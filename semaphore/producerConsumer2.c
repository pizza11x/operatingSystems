#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N_BUFF 10
#define MAX_N_THREADS 100

int nItems, nProducer; //Read only for producer and consumer
struct { //data shared for producer and consumer
    int buff[N_BUFF];
    int nPut;
    int nPutVal;
    sem_t mutex, nEmpty, nStored;
} shared;

#define MIN(a,b) (((a)<(b))?(a):(b))
void *produce(void *), *consume(void *);

int main(int argc, char **argv){
    int i, count[MAX_N_THREADS];
    pthread_t tid_produce[MAX_N_THREADS], tid_consume;
    if(argc != 3){
        printf("usage: producerConsumer <#items> <#producers\n");
        exit(-1);
    }
    nItems = atoi(argv[1]);
    nProducer = MIN(atoi(argv[2]), MAX_N_THREADS);
    //initialize 3 semaphores
    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nEmpty, 0, N_BUFF);
    sem_init(&shared.nStored, 0,0);

    //Create a thread producer ad a thread consumer
    for(i = 0; i<nProducer; i++){
        pthread_create(&tid_produce[i], NULL, produce, &count[i]);
    }
    pthread_create(&tid_produce, NULL, consume, NULL);

    //Wait the two threads
    for(i= 0; i <nProducer; i++){
        pthread_join(tid_produce[i], NULL);
        printf("count[%d] = %d\n", i, count[i]);
    }
    pthread_join(tid_consume, NULL);

    //remove semaphores
    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nEmpty);
    sem_destroy(&shared.nStored);

    return 0;
}

void *produce(void *arg){
    while(1){
        sem_wait(&shared.nEmpty);
        //Wait a empty place
        sem_wait(&shared.mutex);
        if(shared.nPut >= nItems){
            sem_post(&shared.nEmpty);
            sem_post(&shared.mutex);
            return (NULL); //all produced
        }
        shared.buff[shared.nPut % N_BUFF] = shared.nPutVal;
        shared.nPut++;
        shared.nPutVal++;

        sem_post(&shared.mutex);
        sem_post(&shared.nStored);
        //another elemen is available
        *((int *) arg) += 1;
    }
}

void *consume(void *arg){
    int i;
    for(i = 0; i < nItems; i++){
        sem_wait(&shared.nStored);
        //wait an element
        sem_wait(&shared.mutex);
        if(shared.buff[i % N_BUFF] != i){
            printf("error: buff[%d] = %d\n", i, shared.buff[i%N_BUFF]);
        }
        sem_post(&shared.mutex);
        sem_post(&shared.nEmpty); //another free place
    }
    return (NULL);
}