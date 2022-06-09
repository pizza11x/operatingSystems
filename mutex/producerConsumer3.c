#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_ITEMS 1000000
#define MAX_THREADS 100

//Gloabl variables shared with thread
int nItems; //only read for prod. and cons.
int buff[MAX_ITEMS];

struct{
    pthread_mutex_t mutex;
    int nPut; //next index to save
    int nVal; //next value to save
} put = {PTHREAD_MUTEX_INITIALIZER};

struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int nready; //number used by consumer
} nready = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

#define MIN(a,b) (((a)<(b))?(a):(b))
void *produce(void *), *consume(void *);

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
        pthread_mutex_lock(&put.mutex);
        if(put.nPut >= nItems){
            pthread_mutex_unlock(&put.mutex);
            return(NULL); // array full
        }
        buff[put.nPut] = put.nVal;
        put.nPut++;
        put.nVal++;
        pthread_mutex_unlock(&put.mutex);

        pthread_mutex_lock(&nready.mutex);
        if(nready.nready == 0){
            pthread_cond_signal(&nready.cond);
        }
        nready.nready++;
        pthread_mutex_unlock(&nready.mutex);

        *((int *) arg) += 1;
    }
}

void *consume(void *arg){
    int i;
    for(i = 0; i < nItems; i++){
        pthread_mutex_lock(&nready.mutex);
        while(nready.nready == 0){
            pthread_cond_wait(&nready.cond, &nready.mutex);
        }
        nready.nready--;
        pthread_mutex_unlock(&nready.mutex);

        if(buff[i] != i){
            printf("buff[%d] = %d\n", i, buff[i]);
        }
    }
    return(NULL);
}
