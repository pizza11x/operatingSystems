#include "../apue.h"
int main(void){
    //stamp userID and groupID
    printf("uid = %d, gid = %d\n", getuid(), getgid());
    exit(0);
}