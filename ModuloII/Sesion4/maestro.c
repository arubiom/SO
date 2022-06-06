/**
 * @file maestro.c
 * @author Alejandro Rubio Martinez
 * @brief programa maestro del calculo de primos
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

int error;

int main(int argc, char** argv) {
    int pid, mitad_num, leidos, estado;
    char max[10], min[10], mitad[10];
    int primo;
    int fd1[2], fd2[2];

    if (argc != 3) {
        perror("formato");
        exit(-1);
    }
    
    setvbuf(stdout, NULL, _IONBF, 0);

    strcpy(min, argv[1]);
    strcpy(max, argv[2]);

    //Primera mitad del intervalo
    pipe(fd1);
    pipe(fd2);

    mitad_num = (atoi(min)+atoi(max))/2;
    sprintf(mitad, "%d", mitad_num);

    if ((pid = fork()) < 0) {
        perror("fork1");
        exit(-1);
    }

    if (pid == 0) {
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO);

        if (execl("./esclavo", "esclavo", min, mitad, NULL) < 0) {
            perror("exec1");
            exit(-1);
        }

        //sleep(2);
        exit(0);

    } else {
        close(fd1[1]);
        //waitpid(pid, &estado, 0);

        while ((leidos = read(fd1[0], &primo, sizeof(int))) == 4) {
            printf("%d ", primo);
        }

        close(fd1[0]);

        //Segunda mitad del intervalo
        mitad_num++;
        sprintf(mitad, "%d", mitad_num);

        if ((pid = fork()) < 0) {
            perror("fork2");
            exit(-1);
        }

        if (pid == 0) {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);

            if (execl("./esclavo", "esclavo", mitad, max, NULL) < 0) {
                perror("exec2");
                exit(-1);
            }

            //sleep(2);
            exit(0);

        } else {
            //waitpid(pid, &estado, 0);
            close(fd2[1]);

            while ((leidos = read(fd2[0], &primo, sizeof(int))) == 4) {
                printf("bro");
                printf("%d ", primo);
            }

            close(fd2[0]);
        }
        
        return 0;
    }
}