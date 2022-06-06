#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    struct sigaction sig;

    //para matar al programa kill -9 <pid>
    
    sigemptyset(&sig.sa_mask);
    sigfillset(&sig.sa_mask);
    sigdelset(&sig.sa_mask, SIGUSR1);
    sigsuspend(&sig.sa_mask);
}