#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int pid, i;
    short int plano = 0;
    char parametros[100];

    if (argc == 1) {
        printf("Error %d en el formato", errno);
        perror("formato");
        exit(EXIT_FAILURE);
    }

    strcpy(parametros, "");

    for (i = 2; i < argc; i++) {
        if (strcmp(argv[i], "bg")) {
            strcat(parametros, argv[i]);
		    strcat(parametros, " ");
        }
        else
            strcat(parametros, "&");
    }


    if ((pid = fork()) < 0) {
        printf("Error %d en el fork", errno);
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if ((execl(argv[1],parametros,parametros,NULL)<0)) {
            printf("Error %d en el exec\n", errno);
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}