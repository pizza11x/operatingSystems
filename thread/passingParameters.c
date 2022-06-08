#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//Parameters for char_print
struct char_print_parms{
    char character;
    int count;
};
void *char_print (void *parameters){
    //Cast pointer to corret type
    struct char_print_parms* p= (struct char_print_params *) parameters;
    int i;
    for(i=0; i<p->count; i++){
        printf("The char is: %c\n", p->character);
    }
    return NULL;
}

int main(){
    pthread_t tid1, tid2;
    struct char_print_parms tid1_args, tid2_args;

    //Create a thread to stamp 3 'x'
    tid1_args.character = 'x';
    tid1_args.count = 3;
    pthread_create(&tid1, NULL,char_print, (void *)&tid1_args);

    //Create a threa to stamp 5 'y'
    tid2_args.character = 'y';
    tid2_args.count = 5;
    pthread_create(&tid2, NULL,char_print, (void *)&tid2_args);
    
    sleep(1);
    return 0;
}