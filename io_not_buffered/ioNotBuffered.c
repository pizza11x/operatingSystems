#include "./apue.h"
#define BUFFER_SIZE 8192

int main(void){
    int n;
    char buf[BUFFER_SIZE];
    while((n = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0){
        if(write(STDOUT_FILENO, buf, n) != n){
            err_sys("Write error!");
        }
    }
    if(n < 0){
        err_sys("Read error!");
    }
    
    exit(0);
}