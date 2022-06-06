/** Producer: create a FIFO if request, then write data **/
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
#define TEN_MEG (1024 * 1000 *10)

int main(){
    int pipe_fd, res, open_mode = O_WRONLY, bytes_sent = 0;
    char buffer[BUFFER_SIZE];
    if(access(FIFO_NAME, F_OK) == -1){
        res = mkfifo(FIFO_NAME, 0777);
        if(res != 0){
            printf("Could not create fifo %s\n", FIFO_NAME);
            exit(-1);
        }
    }
    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d result: %d\n", getpid(), pipe_fd);
    if(pipe_fd != -1){
        while(bytes_sent < TEN_MEG){
            //Suppose the buffer is filled elsewhere
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            if( res == -1){
                printf("Write error!\n");
                exit(-1);
            }
            bytes_sent += res;
        }
        close(pipe_fd);
    }else{
        printf("Pipe error!\n");
        exit(-1);
    }
    printf("Process %d finished\n", getpid());

    return 0;
}