#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int i;
    struct stat buff;
    char *ptr;
    for(i=1; i<argc; i++){
        printf("%s --> ", argv[i]);
        if(lstat(argv[i], &buff) <0){
            printf("lstat error!\n");
            continue;
        }
        if(S_ISREG(buff.st_mode))   ptr = "regular";
        else if(S_ISBLK(buff.st_mode))  ptr = "block special";
        else if(S_ISLNK(buff.st_mode))  ptr = "symbolic link";
        else if(S_ISDIR(buff.st_mode))  ptr = "directory";
        else if(S_ISCHR(buff.st_mode))  ptr = "character device";
        else if(S_ISFIFO(buff.st_mode))     ptr = "FIFO";
        else if(S_ISSOCK(buff.st_mode))     ptr = "socket";
        else    ptr = "** unknown mode **";

        printf("%s\n", ptr);
    }

    exit(0);
}