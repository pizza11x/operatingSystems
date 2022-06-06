#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int main(){
    int sockfd, len, result;
    struct sockaddr_un address;
    char ch = 'A';
    //Create a client socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    //Define server socket settings 
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
    //Connect us socket with server socket
    result = connect(sockfd, (struct sockaddr*) &address, len);
    if(result == -1){
        perror("Error connect!\n");
        exit(-1);
    }
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);


    return 0;
}