#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int fd, pid;
    char direccion;

    if (argc != 4) {
        perror("formato");
        exit(-1);
    }

    if (strcmp(argv[2], "<") != 0 && strcmp(argv[2], ">") != 0) {
        perror("formato");
        exit(-1);
    }

    setvbuf(stdout, NULL, _IONBF, 0);

    direccion = argv[2][0];

    if ((fd = open(argv[3], O_CREAT | O_WRONLY, 0222)) < 0) {
        perror("open");
        exit(-1);
    }

    if (direccion == '<') {
        close(1);
        if (fcntl(fd, F_DUPFD, 1) < 0) {
            perror("fcntl1");
            exit(-1);
        }
    } else {
        close(0);
        if (fcntl(fd, F_DUPFD, 0) < 0) {
            perror("fcntl2");
            exit(-1);
        }
    }

    if (execlp(argv[1],"", NULL) < 0) {
        perror("exec");
        exit(-1);
    }
}