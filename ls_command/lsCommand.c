#include <sys/types.h>
#include <dirent.h>
#include "../apue.h"

int main(int argc, char *argv[]){
    DIR *dp;
    struct dirent *dirp;
    //Check number of arguments
    if(argc !=2){
        err_quit("a single argument (the dir name) is required");
    }
    //Check DIR
    if((dp = opendir(argv[1]))== NULL){
        err_sys("can't open %s", argv[1]);
    }
    //Write all file name in DIR
    while((dirp = readdir(dp)) != NULL){
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);
}
