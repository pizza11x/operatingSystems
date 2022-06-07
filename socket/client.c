#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    int sockfd, len, result;
    struct sockaddr_in address;
    char ch = 'A';
    //Create a client socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9000);
    len = sizeof(address);
    //connect us socket to server socket
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if(result == -1){
        perror("Connection error!\n");
        exit(-1);
    }
    //We can read and write from socket
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("Char from the server = %c\n", ch);

    close(sockfd);
    return 0;
}