#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    int pid, n;
    short int par = 0, por4 = 0;

    if (argc != 2) {
        printf("Error en el formato: ./prueba <numero>\n");
        perror("formato");
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);

    if ((pid = fork()) < 0) {
        printf("Error %d en el fork", errno);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (n % 4 == 0)
            por4 = 1;
    } else {
        if (n % 2 == 0)
            par = 1;
    }

    if (por4)
        printf("El numero %d es divisible por 4\n", n);
    else if (par)
        printf("El numero %d es par\n", n);
    else
        printf("No es divisible por 2 ni 4\n");
}