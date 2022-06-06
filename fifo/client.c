#include "client.h"
#include <ctype.h>

int main(){
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data;
    char client_fifo[256];
    server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
    if( server_fifo_fd == -1){
        fprintf(stderr, "Sorry, no server\n");
        exit(-1);
    }
    my_data.client_pid = getpid();
    sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
    if(mkfifo(client_fifo, 0777) == -1){
        fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
        exit(-1);
    }
    //Send data to server. Close Fifo Server and remove Fifo Client from memory
    sprintf(my_data.data, "Hello from %d", my_data.client_pid);
    printf("%d sent %s, ", my_data.client_pid, my_data.data);
    write(server_fifo_fd, &my_data, sizeof(my_data));
    client_fifo_fd = open(client_fifo, O_RDONLY);
    if(client_fifo_fd != -1){
        if(read(client_fifo_fd, &my_data, sizeof(my_data)) > 0){
            printf("received: %s\n", my_data.data);
        }
        close(client_fifo_fd);
    }
    close(server_fifo_fd);
    unlink(client_fifo);

    return 0;
}