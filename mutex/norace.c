#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int myGlobal;

void *thread_function(void *);
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    pthread_t myThread;
    int i;
    if(pthread_create(&myThread, NULL, thread_function, NULL)){
        printf("Creation thread failed!\n");
        exit(-1);
    }
    for(i = 0; i<20; i++){
        pthread_mutex_lock(&myMutex);
        myGlobal += 1;
        pthread_mutex_unlock(&myMutex);
        printf("o");
        fflush(stdout);
        sleep(1);
    }
    if(pthread_join(myThread, NULL)){
        printf("Join thread failed!\n");
        exit(-2);
    }
    fflush(stdout);
    printf("\nmyGlobal is equal to %d\n", myGlobal);
    return 0;
}

void *thread_function(void *arg){
    int i,j;
    for(i = 0; i<20; i++){
        pthread_mutex_lock(&myMutex);
        j = myGlobal;
        j += 1;
        printf(".");
        fflush(stdout);
        sleep(1);
        myGlobal = j;
        pthread_mutex_unlock(&myMutex);
    }
    return NULL;
}
