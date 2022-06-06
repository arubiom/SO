/*
contador.c
Alejandro Rubio Martinez
77174857J
20/12/2021
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int contador = 0; //Variable que va a contar la señal

/**
 * @brief El manejador que usaremos para la señal SIGUSR1
 * 
 * @param signum El codigo de la señal
 */
void handler(int signum) {
    if (signum == SIGUSR1) {
        contador++;
    }
    printf("SIGUSR1 recibida %d veces\n", contador);
}

int main(int argc, char **argv) {
    struct sigaction sig; //La accion de la señal
    int iteraciones;

    //Empezamos diciendole el handler que vamos a usar
    sig.sa_handler = handler;

    //Ponemos la mascara de la señal a vacio
    sigemptyset(&sig.sa_mask);

    //Comprobamos que es la señal que queremos
    if (sigaction(SIGUSR1, &sig, NULL) < 0) {
        perror("Recibo de señal");
        exit(-1);
    }

    //Vamos a enviarla 10 veces a el mismo
    iteraciones = 10;
    while(contador < 10) {
        kill(getpid(), SIGUSR1);
    }

}