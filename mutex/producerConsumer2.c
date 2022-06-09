#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_ITEMS 1000000
#define MAX_THREADS 100

int nItems; //Read only

struct{
    pthread_mutex_t mutex;
    int buff[MAX_ITEMS];
    int nPut;
    int nVal;
} shared = { PTHREAD_MUTEX_INITIALIZER };

#define MIN(a,b) (((a)<(b))?(a):(b))
void *produce(void *), *consume(void *), consumeWait(int);

int main(int argc, char **argv){
    int i, nThreads, count[MAX_THREADS];
    pthread_t tidProduce[MAX_THREADS], tidcConsume;
    if( argc != 3){
        printf("Usage: prodcons <#items> <#threads>");
        exit(-1);
    }
    nItems = MIN(atoi(argv[1]), MAX_ITEMS);
    nThreads = MIN(atoi(argv[2]), MAX_THREADS);
    //Start all producers
    for(i = 0; i < nThreads; i++){
        count[i] = 0;
        pthread_create(&tidProduce[i], NULL, produce, &count[i]);
    }
    //Start consumer
    pthread_create(&tidcConsume, NULL, consume, NULL);

    //Wait all thread producer and consumer
    for(i = 0; i < nThreads; i++){
        pthread_join(tidProduce[i], NULL);
        printf("count[%d] = %d\n",i, count[i]);
    }
    pthread_join(tidcConsume, NULL);

    return 0;
}

void *produce(void *arg){
    while(1){
        pthread_mutex_lock(&shared.mutex);
        if(shared.nPut > nItems){
            pthread_mutex_unlock(&shared.mutex);
            return(NULL); // array full
        }
        shared.buff[shared.nPut] = shared.nVal;
        shared.nPut++;
        shared.nVal++;
        pthread_mutex_unlock(&shared.mutex);
        *((int *) arg) += 1;
    }
}

void *consume(void *arg){
    int i;
    for(i = 0; i < nItems; i++){
        consumeWait(i);
        if(shared.buff[i] != i){
            printf("buff[%d] = %d\n", i, shared.buff[i]);
        }
    }
    return(NULL);
}

void consumeWait(int i){
    while(1){
        pthread_mutex_lock(&shared.mutex);
        if(i < shared.nPut){
            pthread_mutex_unlock(&shared.mutex);
            return; //an element is ready
        }
        pthread_mutex_unlock(&shared.mutex);
    }
}
