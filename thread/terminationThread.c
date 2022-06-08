#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thr_fn1(void* arg){
    printf("Thread 1 returning\n");
    return((void *) 1);
}

void* thr_fn2(void* arg){
    printf("Thread 2 existing\n");
    return((void *) 2);
}

int main(){
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if(err != 0){
        printf("Can't create thread 1\n");
        exit(-1);
    }
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if(err != 0){
        printf("Can't create thread 2\n");
        exit(-1);
    }
    err = pthread_join(tid1, &tret);
    if(err != 0){
        printf("Can't join with thread 1\n");
        exit(-1);
    }
    printf("Thread 1 exit code %ld \n", (long)tret);
    err = pthread_join(tid2, &tret);
    if(err != 0){
        printf("Can't join with thread 2\n");
        exit(-1);
    }
    printf("Thread 2 exit code %ld \n", (long)tret);

    return 0;
}
