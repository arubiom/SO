/*
Alejandro Rubio Martínez DGIIM
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main() {
    pid_t pid1, pid2;
    struct stat atributos1, atributos2;
    int fd1[2], fd2[2];
    int fdnew;
    char cadena[256], aux1[256], aux2[256];

    if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf");
        exit(EXIT_FAILURE);
    }

    do {
      pipe(fd1);
      pipe(fd2);
      if (((pid1 = fork()) < 0) || ((pid2 = fork()) < 0)) {
        perror("Error en los fork");
        exit(EXIT_FAILURE);
      }
       
      if (pid1 != 0 && pid2 != 0) {
          close(fd1[0]);
          close(fd2[0]);

          scanf("%s", cadena);
          if ((fdnew = open(cadena, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0) {
              perror("Error al abrir el archivo");
              exit(EXIT_FAILURE);
          }

          if (write(fd1[1], cadena, strlen(cadena)) < 0) {
              perror("Error al escribir en el primer pipe");
              exit(EXIT_FAILURE);
          }

          if (write(fd2[1], cadena, strlen(cadena)) < 0) {
              perror("Error al escribir en el segundo pipe");
              exit(EXIT_FAILURE);
          }
        }
        if (pid1 == 0) {

            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);

            if (read(fd1[0], &aux1, strlen(aux1)) < 0) {
                perror("Error al leer del pipe");
                exit(EXIT_FAILURE);
            }
                         
            //aqui deberiamos usar lstat pero no me ha dado tiempo

            if (atributos1.st_ino % 2 == 0)
                printf("Soy el hijo 1 y es un inodo par");
            else
                printf("Soy el hijo 1 y es un inodo impar");
          
            exit(EXIT_SUCCESS);
        }
        else if (pid2 == 0) {

            close(fd2[1]);
            close(fd1[0]);
            close(fd1[1]);

            if (read(fd2[0], &aux2, strlen(aux2)) < 0) {
                perror("Error al leer del pipe");
                exit(EXIT_FAILURE);
            }
                              
            chmod(aux2, 0666);

            exit(EXIT_SUCCESS);
        }
    } while(strcmp(cadena,"fin") != 0);
}
