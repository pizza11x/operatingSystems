#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pid;
    printf("Sono il processo di partenza con PID %d e PPID %d.\n", getpid(), getppid());

    //Duplicazione. Figlio e genitore continuano da qui
    pid = fork();
    //PID not equals to 0, is parent

    if(pid != 0){
        printf("Sono il processo padre con PID %d e PPID %d.\n", getpid(), getppid());
        printf("Il PID del mio figlio e' %d.\n", pid); //non aspetta con wait()
    }else{
        printf("Sono il processo figlio con PID %d e PPID %d.\n", getpid(), getppid());
    }
    printf("PID %d termina.\n", getpid());

    return 0;
}