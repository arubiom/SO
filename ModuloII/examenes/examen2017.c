/* Desarrolle un programa C,utilizando llamadas al sistema y haciendo uso de los mecanismos que considere oportunos,
que lleve a cabo el duplicado exacto de todos los archivos contenidos en un directorio fuente(primer argumento) que 
son de tipo regular en otro directori odestino(que pasa com osegundo argumento).si el directorio destino no existe 
entonces se creará.

Extienda el programa anterior,de tal forma que sin utilizar la llamada al sistema nftw:

a) El programa lanzara un nuevo proceso hijo para realizar la misma función del ejercicio anterior para cada uno de los
subdirectorios contenidos en el directorio fuente es decir , duplicando los archivos de tipo regular que se encuentren 
cada uno de dichos subdirectorio en el directorio destino cada proceso que recorra un subdirectorio realizara la misma 
accion para los subdirectorios que a su vez incluya ,es decir,lanzará un nuevo proceso para recorrer cada uno de dichos 
subdirectorios,duplicando los archisvos regulares en el directorio destino.
No deben quedar procesos en estado zombie.

b) Cuando cada proceso acabe de recorrer y duplicar todos los archivos regulares del directorio en cuestión, comunicara 
por medio de un cauce a su proceso padre(o alternativamente al proceso inicial,el estudiante puede escoger entre esta 
segunda opción que es mas facil de implementar)el numero de archivos que ha duplicado tanto él como sus hijos , y asi 
repetidamente para cada proceso.El proceso inicial imprimirá en pantalla el numero total de archivos duplicados por todos 
los procesos.
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

/**
 * @brief Recorre recursivamente un directorio
 * 
 * @param path El directorio que queremos recorrer
 * @param dest EL directorio al que copiaremos los archivos regulares
 * @return int El numero de archivos regulares en el directorio
 */
int recorrer(char* path, char* dest);
int pid;

int main(int argc, char** argv) {
    char destino[100], origen[100];
    struct stat st;
    DIR *directorio;
    int regulares, fd;

    setvbuf(stdout, NULL, _IONBF, 0);

    //Comprobamos que el formato de ejecucion sea el adecuado
    if (argc != 3) {
        printf ("Ejecucion: ./examen2017 <origen> <destino>");
        perror("formato");
        exit(-1);
    }

    strcpy(origen, argv[1]);
    strcpy(destino, argv[2]);

    if (stat(destino, &st) < 0) {
        mkdir(destino, 0700);
    }

    //Abrimos el directoripo de destino
    if ((directorio = opendir(destino)) < 0) {
        perror("open destino");
        exit(-1);
    }

    regulares = recorrer(origen, destino);

    if (pid > 0) {
        printf("Se han encontrado %d archivos regulares recursivamente en %s\n", regulares, origen);
    }

    return 0;
}

int recorrer(char* path, char* dest) {
    int ret = 0, rethijo = 0;
    int aux;
    int estado;
    int fd[2];
    DIR *directorio;
    struct stat atributos;
    struct dirent *archivo;
    char ruta_archivo[500];

    pipe(fd);

    //Creamos un proceso hijo
    if ((pid = fork()) < 0) {
        perror("Error en el fork");
        return -1;
    }

    if (pid == 0) { //El hijo
        close(fd[0]);   //Cerremos la lectura del cauce

        //Abrimos el directorio
        if ((directorio = opendir(path)) < 0) {
            perror("Error al abrir");
            return -1;
        }

        //Empezamos a leer los archivos
        while((archivo = readdir(directorio)) != NULL) {
            //Calculamos la ruta absoluta del archivo
            sprintf(ruta_archivo, "%s/%s", path, archivo->d_name);

            //Obtenemos los metadatos del archivo
            if (stat(ruta_archivo, &atributos) < 0) {
                perror("stat");
                return -1;
            }

            //Vamos a comprobar que tipo de archivo tenemos
            if (S_ISREG(atributos.st_mode)) {
                rethijo++;

                //Ejecutamos la orden cp que copiara el fichero al otro directorio
                execl("cp", "cp", ruta_archivo, dest, NULL);

             //Comprobamos que se un directorio y distinto de .. y .    
            } else if (S_ISDIR(atributos.st_mode) && strcmp(archivo->d_name, ".") != 0 && strcmp(archivo->d_name, "..") != 0) {
                //Volvemos a llamar recursivamente a la funcion
                if ((aux = recorrer(ruta_archivo, dest)) == -1) {
                    perror("Fallo en la recursividad");
                    return -1;
                } else {
                    rethijo+=aux;
                }
            }
        }
        //Escribimos el valor en el cauce
        if (write(fd[1], &rethijo, sizeof(int)) != 4) {
            perror("write");
            return -1;
        }

        closedir(directorio);
        //Terminamos el hijo
        exit(0);
    } else {
        close(fd[1]);
        waitpid(pid, &estado, 0); //El padre espera a que termine el hijo

        //Vamos a leer lo que ha escrito el hijo
        if (read(fd[0], &ret, sizeof(int)) != 4) {
            perror("read del cauce");
            return -1;
        }
        

        close(fd[0]);
        return ret;
    }
}