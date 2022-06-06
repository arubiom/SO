/*
Realizar un programa recorrer.c que reciba como único argumento una ruta a un directorio. De esta manera,
la invocación se hará de la siguiente manera:

    ./recorrer <ruta_directorio>

Al comenzar deberá mostrar su PID y el PID de su padre. A continuación deberá recorrer las entradas del 
directorio y para cada entrada de tipo directorio (que no sea . ni ..)
deberá crear un hijo. Cuando haya recorrido todas las entradas, se quedará esperando a que terminen sus hijos.
Para cada uno, indicará su PID y el valor que ha devuelto.

Cada uno de los hijos deberá:
    1. Mostrar su PID y el de su padre
    2. recorrer el directorio que se ha identificado sumando los tamaños de todos los archivos
    regulares que encuentre y contando cuantos son.
    3. Al terminar de recorrer el directorio, mostrará un mensaje indicando el directorio y la
    suma de tamaños.
    4. Devolverá al terminar como resultado el número de archivos regulares que ha
    encontrado (si es superior a 255, devolverá 255).

Se tendrá en cuenta para la calificación del programa:
    1. La claridad de la programación.
    2. El tratamiento de errores.
    3. Los comentarios explicando el código.
*/

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

int main(int argc, char** argv) {

    //Declaracion de varibles
    char ruta[100];
    DIR *directorio, *subdirectorio;
    struct dirent *archivo, *subarchivo;
    struct stat atributos, subatributos;
    char ruta_archivo[120], ruta_subarchivo[140];
    int pid, contadorregs = 0, bytes = 0, estado;
    
    //Comprobamos que la ejecucion sea correcta
    if (argc != 2) {
        printf("Error en la ejecucion: ./recorrer <ruta_directorio>");
        exit(-1);
    }

    //Vaciamos el buffer de la salida por defecto
    setvbuf(stdout, NULL, _IONBF, 0);

    strcpy(ruta, argv[1]);

    printf("Soy el proceso con PID %d y mi padre tiene PID %d\n", getpid(), getppid());

    //Abrimos el directorio que se nos indica
    if ((directorio = opendir(ruta)) < 0) {
        perror("Apertura directorio");
        exit(-1);
    }

    //Vamos leyendo todos los archivos del directorio
   while ((archivo = readdir(directorio)) != NULL) {
        sprintf(ruta_archivo, "%s/%s", ruta, archivo->d_name);

        //Obtencion de los metadatos del archivo
       if (stat(ruta_archivo, &atributos) < 0) {
           printf("Error en el stat de %s\n", ruta_archivo);
           perror("Stat fichero");
           exit(-1);
       }

        //Comprobamos las condiciones del enunciado
       if (S_ISDIR(atributos.st_mode) && strcmp(archivo->d_name, ".") != 0 && strcmp(archivo->d_name, "..") != 0) {
           //Creacion de un hijo
           if ((pid = fork()) < 0) {
               perror("Fork");
               exit(-1);
            }
            if (pid == 0) { //El hijo

                printf("Soy un hijo con PID %d y mi padre tiene PID %d\n", getpid(), getppid());

                //Abrimos el subdirectorio
                if ((subdirectorio = opendir(ruta_archivo)) < 0) {
                    perror("Apertura subdirectorio");
                    exit(-1);
                }
                contadorregs = 0;
                //Vamos comprobando todos los archivos en el subdirectorio
                while ((subarchivo = readdir(subdirectorio)) != NULL) {
                    sprintf(ruta_subarchivo, "%s/%s", ruta_archivo, subarchivo->d_name);

                    //Obtencion de los metadatos
                    if (stat(ruta_subarchivo, &subatributos) < 0) {
                        printf("Error en el stat de %s\n", ruta_subarchivo);
                        perror("Stat subarchivo");
                        exit(-1);
                    }

                    //Comprobamos que sea regular
                    if (S_ISREG(subatributos.st_mode)) {
                        contadorregs++;
                        bytes += subatributos.st_size;
                    }
                }

                printf("El directorio %s tiene %d archivos regulares que ocupan %d bytes\n\n", ruta_archivo, contadorregs, bytes);
                exit(0);
            } else { //El padre
                //Esperamos a que el hijo termine
                waitpid(pid, &estado, 0);
            }
       }
   } 
}