#include "client.h"
#include <ctype.h>

int main(){
    int server_fifo_fd, client_fifo_fd;
    struct data_to_pass_st my_data; //Struct to read and return
    int read_res;
    char client_fifo[256]; //for the Client Fifo name
    char *tmp_char_ptr;
    mkfifo(SERVER_FIFO_NAME, 0777);
    server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY);
    if(server_fifo_fd == -1){
        printf("Server fifo failure!\n");
        exit(-1);
    }
    sleep(10); //Queue clients for demonstration purposes
    do{
        read_res = read(server_fifo_fd, &my_data, sizeof(my_data));
        if(read_res > 0){
            //Convert all letters in CAPS and add pid to CLIENT_FIFO_NAME
            tmp_char_ptr = my_data.data;
            while(*tmp_char_ptr){
                *tmp_char_ptr = toupper(*tmp_char_ptr);
                tmp_char_ptr++;
            }
            sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
            //return data open client pipe
            client_fifo_fd = open(client_fifo, O_WRONLY);
            if( client_fifo_fd != 1){
                write(client_fifo_fd, &my_data, sizeof(my_data));
                close(client_fifo_fd);
            }
        }
    } while( read_res > 0);
    close(server_fifo_fd);
    unlink(SERVER_FIFO_NAME);

    return 0;
}