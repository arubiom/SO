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
    int fifo;
    int value = 5;
    char leido[5];
    pid_t pid;

    fifo = mkfifo("elfifo", 0600);

    pid = fork();

    if (pid == 0) {
        write(fifo, "hola", 4);
        close(fifo);
    } else {
        read(fifo, leido, 4);

        printf("%s", leido);
        close(fifo);
    }
}