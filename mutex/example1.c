#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

pthread_mutex_t M; //def.mutex shared by thread
int DATA = 0;
int access1 = 0; //num. access thread 1 to critical section
int access2 = 0; //num. access thread 2 to critical section

void *thread1_process(void * arg){
    int k=1;
    while(k){
        access1++;
        pthread_mutex_lock(&M);
        DATA++;
        k = (DATA > MAX?0:1);
        pthread_mutex_unlock(&M);
        printf("Access T1: %d\n", access1);
        sleep(1);
    }
    pthread_exit(0);
}

void *thread2_process(void * arg){
    int k = 1;
    while(k){
        access2++;
        pthread_mutex_lock(&M);
        DATA++;
        k = (DATA >= MAX ? 0 : 1);
        pthread_mutex_unlock(&M);
        printf("Access T2: %d\n", access2);
        sleep(1);
    }
    pthread_exit(0);
}

int main(){
    pthread_t th1, th2; //mutex start free
    pthread_mutex_init(&M, NULL);
    if(pthread_create(&th1, NULL, thread1_process, NULL) < 0){
        fprintf(stderr, "Creation thread 1 error\n");
        exit(1);
    }
    if(pthread_create(&th2, NULL, thread2_process, NULL) < 0){
        fprintf(stderr, "Creation thread 2 error\n");
        exit(1);
    }
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    printf("Access: T1: %d, T2: %d\n", access1, access2);
    printf("Tot access: %d\n", DATA);
    
    return 0;
}