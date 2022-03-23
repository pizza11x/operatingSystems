#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFF_SIZE 4096 
#define RES_SIZE 3 
#define LIMIT 5 

int main(){
    char buff[BUFF_SIZE];
    int fd_in, fd_out;
    int n;

    fd_in = open("inputFile.txt", O_RDONLY | O_CREAT);
    fd_out = open("outputFile.txt", O_WRONLY | O_CREAT);
    if(fd_in == -1 || fd_out == -1){
        printf("ERRR opening the files\n");
        exit(0);
    }
    while( (n = read(fd_in, buff, BUFF_SIZE)) > 0 ){
        if(write(fd_out, buff, n) != n){
            printf("Write error!");
        }
    }
    if(n < 0){
        printf("Read error!");
    }
    exit(0);
}