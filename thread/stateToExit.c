#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread1(void* arg){
    int error;
    error=*(int*)arg;
    printf("I'm the first thread. Parameter= %d\n",*(int*)arg);
    pthread_exit((void *)(long)error);
}

void *thread2(void* arg){
    static long error;
    error=*(int*)arg;
    printf("I'm the second thread. Parameter= %d\n",(int)error);
    pthread_exit((void *)&error);
}
int main(){
    pthread_t th1, th2;
    int i1 = 1, i2 = 2;
    void *exit;
    pthread_create(&th1, NULL, thread1, (void*)&i1);
    pthread_create(&th2, NULL, thread2,(void *)&th2);
    pthread_join(th1, &exit);
    printf("State = %ld\n", (long)exit);
    pthread_join(th2, &exit);
    printf("State = %ld\n", *(long *)exit);
    
    return 0;
}