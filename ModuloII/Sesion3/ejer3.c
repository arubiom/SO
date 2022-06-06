#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int pid;
    int nprocs = 20;

    for (int i = 0; i < nprocs; i++) {
        if ((pid = fork()) < 0) {
            printf("Error %d en fork %d\n", errno, i);
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            printf("Soy un proceso hijo con PID %d y mi padre %d\n", getpid(), getppid());
            break;
        }
    }

    return 0;
}