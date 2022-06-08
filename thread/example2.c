#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 8

void *printHello(void* threadID){
    int *id_ptr, taskID;

    sleep(1);
    id_ptr = (int *)threadID;
    taskID = *id_ptr;
    printf("Thread %d\n", taskID);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int rc, t;
    int *taskIDS[NUM_THREADS];
    for(t = 0; t < NUM_THREADS; t++){
        taskIDS[t] = (int *)malloc(sizeof(int)); //address of a int
        *taskIDS[t] = t; //int
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, printHello, (void *)taskIDS[t]);
        if(rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
}