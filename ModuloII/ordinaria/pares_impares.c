/*
pares_impares <N>
Alejandro Rubio Martinez
77174857J
20/12/2021
*/

#include<sys/types.h>
#include<unistd.h>		
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char** argv) {
    int pid1, pid2;
    int fd1[2], fd2[2];
    int n, suma1 = 0, suma2 = 0, leido;
    int aux;

    //Comprobamos primero el formato de ejecucion
    if (argc != 2) {
        printf("Error en la ejecucion prueba ./pares_impares <N>\n");
        perror("Formato");
        exit(-1);
    }

    //Creamos los cauces
    pipe(fd1);
    pipe(fd2);

    //Obtenemos el entero que hemos pasado como argumento
    n = atoi(argv[1]);

    //Comprobamos que no sea un numero negativo
    if (n < 0) {
        printf("Prueba con un numero positivo\n");
        perror("Negativo");
        exit(-1);
    }

    //Creamos el primer proceso hijo
    if ((pid1 = fork()) < 0) {
        perror("Fork 1");
        exit(-1);
    }
    
    if (pid1 == 0) { //Codigo del hijo
        //Vamos a leer el cauce (es bloquente)
        while (read(fd1[0], &leido, sizeof(int)) == 4) {
            if (leido == -1) {
                break; //Nos salimos del bucle si es un -1
            } else {
                suma1+=leido;
            }
        }

        //vamos a escribir el resultado de la suma en el cauce
        if (write(fd1[1], &suma1, sizeof(int)) != 4) {
            perror("Wirte");
            exit(-1);
        }

        //Ya podemos matar al hijo
        exit(0);
    } else { //codigo del padre
        //Vamos a escribir en el cauce los pares
        for (int i = 0; i <= n; i+=2) {
            aux = i;
            write(fd1[1], &aux, sizeof(int));
        }

        //Vamos a escribir el -1
        aux = -1;
        write(fd1[1], &aux, sizeof(int));

        //Esperamos a que el hijo escriba la suma
        waitpid(pid1, NULL, 0);
        //Ahora vamos a leer el valor
        if (read(fd1[0], &leido, sizeof(int)) != 4) {
            perror("Read 1 padre");
            exit(-1);
        }

        printf("La suma de los pares es %d\n", leido);

        //Vamos ahora con el segundo hijo
        //Creamos el segundo proceso hijo
        if ((pid2 = fork()) < 0) {
            perror("Fork 2");
            exit(-1);
        }
        
        if (pid2 == 0) { //Codigo del hijo
            //Vamos a leer el cauce (es bloquente)
            while (read(fd2[0], &leido, sizeof(int)) == 4) {
                if (leido == -1) {
                    break; //Nos salimos del bucle si es un -1
                } else {
                    suma2+=leido;
                }
            }

            //vamos a escribir el resultado de la suma en el cauce
            if (write(fd2[1], &suma2, sizeof(int)) != 4) {
                perror("Wirte");
                exit(-1);
            }

            //Ya podemos matar al hijo
            exit(0);
        } else { //codigo del padre
            //Vamos a escribir en el cauce los pares
            for (int i = 1; i <= n; i+=2) {
                aux = i;
                write(fd2[1], &aux, sizeof(int));
            }

            //Vamos a escribir el -1
            aux = -1;
            write(fd2[1], &aux, sizeof(int));

            //Esperamos a que el hijo escriba la suma
            waitpid(pid2, NULL, 0);
            //Ahora vamos a leer el valor
            if (read(fd2[0], &leido, sizeof(int)) != 4) {
                perror("Read 2 padre");
                exit(-1);
            }

            printf("La suma de los impares es %d\n", leido);
        }
    }
    return 0;
}