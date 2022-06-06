#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

const int NPROCS = 5;

int main(int argc, char** argv) {
    int estado, hijos = 0;
    int pid[NPROCS];

    for(int i = 0; i < NPROCS; i++) {
        if ((pid[i] = fork()) < 0) {
            printf("Error %d en el fork %d", errno, i);
            exit(EXIT_FAILURE);
        } else {
            hijos++;
        }

        if (pid[i] == 0) {
            printf("Soy el hijo %d\n", getpid());
            exit(0);
        }
    }

    sleep(2);

    for (int i = 0; i < NPROCS; i+=2) {
        waitpid(pid[i], &estado, 0);
        hijos--;

        printf("He terminado el hijo %d y quedan %d\n", pid[i], hijos);
    }

    for (int i = 1; i < NPROCS; i+=2) {
        waitpid(pid[i], &estado, 0);
        hijos--;

        printf("He terminado el hijo %d y quedan %d\n", pid[i], hijos);
    }

    return 0;
}