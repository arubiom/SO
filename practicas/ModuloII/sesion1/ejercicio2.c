/* Programa que lee bloques de n bytes
de un archivo y los escribe en otro */
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc, char* argv[]) {
    int fin, fout;
    char *entrada, *salida;

    //Leemos los ficheros de entrada y salida
    if (argc == 3) {
        entrada = argv[1];
        salida = argv[2];
    }
    else {
        printf("Error en los parametros\n");
    }  

    //Abrimos el fichero de salida
    if (fout = open(salida, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR) < 0) {
        printf("Error al abrir fichero de salida\n");
        exit(EXIT_FAILURE);
    }

    //Abrimos el fichero de entrada
    if (fin = open(entrada, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR) < 0) {
        if (write(fout,"Error no es posible abrir el fichero de entrada",48) < 0) {
            printf("Error de escritura y lectura\n");
        }
        exit(EXIT_FAILURE);
    }

    char* cadena;
    char counter = '1';

    //Bucle que escribe los bloques de 80 en 80
    while (read(fin, cadena, 80) == 80) {
        // cadena += '\\' + 'n';
        // char* bloque = "Bloque " + counter + '\\' + 'n';
        if (write(fout, cadena, 82) != 82) {
            printf("\nError al escribir ejecuccion interrumpida\n");
        }
        counter++;
    }
    

    exit(EXIT_SUCCESS);
}