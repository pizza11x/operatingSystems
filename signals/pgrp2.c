#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigHandler (int sig) {
    printf ("Process %d got a SIGINT\n", getpid()); exit (1);
}

int main (void) {
    int i;
    signal (SIGINT, sigHandler); /* gestore di segnali */
    if (fork () == 0)
        setpgid (0, getpid ());/* il figlio nel suo gruppo */ 
    printf("Process PID %d PGRP %d waits\n",getpid(),getpgid(0)); 
    for (i = 1; i <= 3; i++) { /* Cicla 3 volte */
        printf ("Process %d is alive\n", getpid());
        sleep(2);
    }
    return 0;
}