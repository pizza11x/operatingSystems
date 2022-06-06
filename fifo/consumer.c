#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

int main(){
    int pipe_fd, res, open_mode = O_RDONLY, bytesReads;
    char buffer[BUFFER_SIZE];
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd);
    if(pipe_fd != -1){
        do{
            res = read(pipe_fd, buffer, BUFFER_SIZE);
            bytesReads += res;
        }while( res > 0 );
        close(pipe_fd);

    }else{
        printf("Pipe error!\n");
        exit(-1);
    }

    printf("Process %d finisched, %d bytes read\n", getpid(), bytesReads);

    return 0;
}

