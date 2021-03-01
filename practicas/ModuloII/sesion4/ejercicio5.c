#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {

    int inf, sup, mitad, num;
    int fd1[2], fd2[2], fdm[2];
    pid_t pid1, pid2;

    if (argc != 3)
        perror("Los argumentos son incorrectos");

    inf = atoi(argv[1]);
    sup = atoi(argv[2]);
    mitad = (inf+sup)/2;

    pipe(fd1);
    pipe(fd2);
    pipe(fdm);

    if (pid1 = fork() == 0) {
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[1]);
        close(fdm[0]);

        dup2(fd1[0], STDIN_FILENO);
        dup2(fdm[1], STDOUT_FILENO);

        execlp("./esclavo", "esclavo", inf, mitad, NULL);
    }
    else if (pid2 = fork() == 0) {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[1]);
        close(fdm[0]);

        dup2(fd2[0], STDIN_FILENO);
        dup2(fdm[1], STDOUT_FILENO);

        execl("./esclavo", "esclavo", mitad+1, sup, NULL);
    }
    else {
        close(fd1[0]);
        close(fd2[0]);
        close(fdm[1]);

        while((read(fdm[0], &num, sizeof(int))) != 0){
            printf("%d\n", num);
        }
    }

}