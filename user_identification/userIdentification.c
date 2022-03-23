#include "./apue.h"
int main(){
    //stamp userID and groupID
    printf("uid = %d, gid = %d\n", getuid(), getgid());
    exit(0);
}