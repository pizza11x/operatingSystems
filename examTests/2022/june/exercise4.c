#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 4096

int main(int argc, char** argv){
    int fdFile;
    char buff[BUFF_SIZE];
    int bytesReads;
    int offset = 0;

    printf("Hello Worlds!\n");

    //Check Argument number
    if(argc < 2){
        printf("Usage: %s name_file\n", argv[0]);
        exit(-1);
    }
    
    //Open File
    fdFile = open(argv[1], O_CREAT | O_RDONLY);
    if(fdFile == -1){
        printf("Error reading file!\n");
        exit(-1);
    }

    //Read from file
    while( (bytesReads = read(fdFile, buff, 1)) > 0 ){

        //Write on terminal
        if(write(STDOUT_FILENO, buff, bytesReads) != bytesReads){
            printf("Write error!\n");
            close(fdFile);
            exit(-1);
        }
        offset = offset+2;

        //Set offset to fdFile
        if(lseek(fdFile, offset, SEEK_SET) == -1){
            printf("Lseek error!\n");
            close(fdFile);
            exit(-1);
        }
        
    }
    printf("\n");

    if( bytesReads < 0){
        printf("Read error!\n");
        close(fdFile);
        exit(-1);
    }


    close(fdFile);
    return 0;
}