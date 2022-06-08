#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct char_print_parms{
    char character;
    int count;
};

void *char_print(void * parameters){
    struct char_print_parms* p = (struct char_print_parms *)parameters;
    int i;
    for(i = 0; i< p->count; i++){
        printf("The character is = %c\n", p->character);
    }
    return NULL;
}

int main(){
    pthread_t tid1, tid2;
    struct char_print_parms tid1_params, tid2_params;
    tid1_params.character = 'x';
    tid1_params.count = 30;
    pthread_create(&tid1, NULL, char_print, &tid1_params);

    tid2_params.character = 'y';
    tid2_params.count = 20;
    pthread_create(&tid2, NULL, char_print, &tid2_params);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
    
}