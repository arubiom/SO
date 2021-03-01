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

int main(int argc, char** argv) {

    struct dirent *fichero;
    struct stat atributos;
    DIR *directorio, *directorio2;
    int fdcopia;
    pid_t pid;
    char *namecopia = "", *concatenacion = "", *cadenalstat = ""; 

    //Comprobaciond de errores
    if (argc != 3) {
        perror("Error en el numero de argumentos");
        exit(EXIT_FAILURE);
    }

    //Abrimos el directorio de origen
    if ((directorio = opendir(argv[1])) == NULL) {
        perror("Error al abrir el directorio 1");
        exit(EXIT_FAILURE);
    }

    //Abrimos el directorio destino y si no existe lo creamos
    if ((directorio2 = opendir(argv[2])) == NULL) {
        if (mkdir(argv[2], 0777) < 0) {
            perror("Error en el mkdir");
            exit(EXIT_FAILURE);
        }

        if ((directorio2 = opendir(argv[2])) == NULL) {
            perror ("Error al reintentar abrir el segundo directorio");
            exit(EXIT_FAILURE);
        }
    }

    //Creamos el fichero copia.txt 
    namecopia = malloc(strlen(argv[2])+13);
    sprintf(namecopia, "%s/copiados.txt", argv[2]);
    if ((fdcopia = open(namecopia, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR)) < 0) {
        perror("Error al crear copiados.txt");
        exit(EXIT_FAILURE);
    }

    while ((fichero = readdir(directorio)) != 0) {

        //Cogemos los atributos del fichero que acabamos de coger
        cadenalstat = malloc(strlen(argv[1])+25);
        sprintf(cadenalstat, "%s/%s", argv[1], fichero->d_name);
        if (lstat(cadenalstat, &atributos) < 0) {
            printf("%s\n", cadenalstat);
            perror("Error en lstat\n");
            exit(EXIT_FAILURE);
        }

        //Comprobamos que tiene los atributos especificados en el enunciado
        if (S_ISREG(atributos.st_mode) && atributos.st_size >= 1024) {

            if ((pid = fork()) < 0) {
                perror("Error en el fork");
                exit(EXIT_FAILURE);
            }
            //Ahora nuestro proceso hijo procederá a ejecutar cp
            else if (pid == 0) {
                execlp("cp", "cp", cadenalstat, argv[2], NULL);
            }

            //Escribimos lo que nos pide en copiados.txt
            concatenacion = malloc(strlen(fichero->d_name) + 4 + 10);
            sprintf(concatenacion, "%s | %d | %d", fichero->d_name, atributos.st_mode, fichero->d_ino);
            if (write(fdcopia, &concatenacion, sizeof(concatenacion)) < 0) {
                printf("Error al escribir en copiados.txt");
                exit(EXIT_FAILURE);
            }
        }
    }

    //Cerramos todo lo que teniamos abierto
    close(fdcopia);
    closedir(directorio);
    closedir(directorio2);
    return 0;
}