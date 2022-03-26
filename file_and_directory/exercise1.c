#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int main(){
    char c, cwd[100];
    int fd;
    struct stat buff;
    struct dirent *drn;
    DIR *dp;
    getcwd(cwd, sizeof(cwd));
    //LOAD THE ATTACHED STRUCT TO DIR
    if((dp = opendir(cwd)) == NULL){
        printf("opendir error!\n");
        exit(-1);
    }
    //READ DIR CONTENT
    while((drn = readdir(dp)) != NULL){
        if(lstat(drn->d_name, &buff) <0){
            printf("Error lstat su %s\n", drn->d_name);
        }
        if(S_ISLNK(buff.st_mode)){
            printf("Trovato il link %s\n", drn->d_name);
        }
    }

    closedir(dp);
    exit(0);
}