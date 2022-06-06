/*
buscar .c <cadena> <ruta_directorio>
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
#include<dirent.h>
#include<string.h>
#include<stdlib.h>

/**
 * @brief funcion que buscara recursivamente en un directorio
 * 
 * @param cadena Los archivos que queremos buscar
 * @param path La ruta del directorio
 */
void buscar(char* cadena, char* path);

int main(int argc, char** argv) {
    char cadena[30];
    char ruta_dir[200];

    //Comprobamos que la ejecucion sea correcta
    if (argc != 3) {
        printf("Error en la ejecucion prueba ./buscar .c <cadena> <ruta_directorio>\n");
        exit(-1);
    }

    strcpy(cadena, argv[1]);
    strcpy(ruta_dir, argv[2]);

    //Llamamos a la funcion buscar
    buscar(cadena, ruta_dir);
}

/*
Implementacion de buscar
*/
void buscar(char* cadena, char* path) {
    DIR *directorio;
    struct dirent *archivo;
    struct stat atributos;
    char ruta_archivo[200];

    //Vamos a abrir el directorio
    if ((directorio = opendir(path)) < 0) {
        printf("Error al abrir el directorio %s", path);
        perror("Opendir");
        exit(-1);
    }

    //Vamos leyendo los archivos que se encuentran en el directorio
    while ((archivo = readdir(directorio)) != NULL) {
        sprintf(ruta_archivo, "%s/%s", path, archivo->d_name); //La ruta absoluta del archivo
        //Vamos a obterner los metadatos del archivo
        if ((stat(ruta_archivo, &atributos)) < 0) {
            printf("Error en los metadatos de %s\n", ruta_archivo);
            perror("stat");
            exit(-1);
        }

        //Vamos a comprobar las condiciones dadas por el enunciado
        if (S_ISREG(atributos.st_mode) && atributos.st_mode & S_IXUSR && strncmp(archivo->d_name, cadena, strlen(cadena)) == 0) {
            printf("%s cumple las condiciones\n", ruta_archivo);
         //Ahora comprobamos si es un directorio
        } else if (S_ISDIR(atributos.st_mode) && strcmp(archivo->d_name, ".") && strcmp(archivo->d_name, "..")) {
            buscar(cadena, ruta_archivo); //Llamada recursiva a la funcion
        }
    }
}