#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *compute_prime(void* arg){
    static int candidate = 2;
    int n = *((int *) arg);
    int factor, is_prime;
    while(1){
        is_prime = 1;
        for(factor = 2; factor < candidate; ++factor){
            if(candidate % factor == 0){
                is_prime = 0;
                break;
            }
        }
        if(is_prime){
            if(--n == 0){
                return (void *)&candidate;
            }
        }
        ++candidate;

    }
    return NULL;
}

int main(){
    pthread_t tid;
    int which_prime = 5000;
    void * prime;
    pthread_create(&tid, NULL,compute_prime, (void *)&which_prime);

    //Wait the calculate
    pthread_join(tid, &prime);
    printf("The %dth prime number is %d.\n", which_prime, *(int *)prime);

    return 0;
}
