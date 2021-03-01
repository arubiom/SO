#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int primo(int n);

int main(int argc, char** argv) {

    int inf, sup;

    if (argc != 3)
        perror("Error en los parametros del esclavo");

    inf = atoi(argv[1]);
    sup = atoi(argv[2]);

    for (int i = inf; i <= sup; i++) {
        if (primo(i))
            write(STDOUT_FILENO, &i, sizeof(i));
    }
}

int primo(int n) {
    for (int i = 2; i < n/2; i++)
        if (n % i == 0)
            return 0;

    return 1;
}