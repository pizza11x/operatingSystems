#include <stdio.h>
#include <stdlib.h>

int main(void){
    int c;
    while((c = getc(stdin)) != EOF ){
        if(putc(c, stdout) == EOF){
            printf("Output error!\n");
            exit(1);
        }
    }
    if(ferror(stdin)){
        printf("Input error!\n");
        exit(1);
    }

    exit(0);
}