#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pthread_t ntid;
void printIds(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", 
        s, 
        (pid_t) pid,
        (unsigned long) tid,
        (unsigned long) tid
    );
}

void *thr_fn(void *args){
    printIds("New thread: ");
    return ((void *) 0);
}

int main(){
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if(err != 0){
        printf("I can't create the thread");
        exit(-1);
    }
    printIds("Thread main:");
    sleep(1);

    return 0;
}