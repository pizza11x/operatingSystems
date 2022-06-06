#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"

int main(int argc, char** argv){
    int res, i, open_mode = 0;
    if(argc < 2){
        printf("Use: %s <combination of O_RDONLY O_WRONLY O_NONBLOCK>\n", argv[0]);
        exit(1);
        
    }
    //Set open_mode value from arguments
    for(i= 1; i < argc; i++){
        if(strncmp(*++argv, "O_RDONLY", 8) == 0) open_mode |= O_RDONLY;
        if(strncmp(*argv, "O_WRONLY", 8) == 0) open_mode |= O_WRONLY;
        if(strncmp(*argv, "O_NONBLOCK", 10) == 0) open_mode |= O_NONBLOCK;

    }
    //Create FIFO if not exists and then open it
    if(access(FIFO_NAME, F_OK) == -1){
        res = mkfifo(FIFO_NAME, 0777);
        if( res != 0){
            printf("I can't create FIFO %s\n", FIFO_NAME);
            exit(1);
        }
    }
    printf("Process %d open the FIFO \n", getpid());
    res = open(FIFO_NAME, open_mode);
    printf("Process result: %d: %d\n", getpid(), res);
    sleep(5);
    if(res != -1) close(res);

    printf("Process %d Terminated!\n", getpid());

    return 0;
}

