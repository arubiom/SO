#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int pid;
    int value = 5;
    int leido;
    int fd[2];

    setvbuf(stdout, NULL, _IONBF, 0);

    pipe(fd);

    pid = fork();

    if (pid == 0) {
        close(fd[0]);
        for (int i = 0; i < value; i++) {
            write(fd[1], &value, sizeof(int));
        }
    } else {
        close(fd[1]);
        while (read(fd[0], &leido, sizeof(int)) == 4) {
            printf("%d ", leido);
        }

        fflush(stdout);
    }
}