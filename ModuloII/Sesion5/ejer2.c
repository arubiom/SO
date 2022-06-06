#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int contador1 = 0;
int contador2 = 0;
int contador3 = 0;
int contador6 = 0;
int contador14 = 0;
int contador15 = 0;

static void handler(int signum) {
    if (signum == 1) {
        contador1++;
        printf("Se ha enviado la señal 1 %d veces\n", contador1);
    } else if (signum == 2) {
        contador2++;
        printf("Se ha enviado la señal 2 %d veces\n", contador2);
    } else if (signum == 3) {
        contador3++;
        printf("Se ha enviado la señal 3 %d veces\n", contador3);
    } else if (signum == 6) {
        contador6++;
        printf("Se ha enviado la señal 6 %d veces\n", contador6);
    } else if (signum == 14) {
        contador14++;
        printf("Se ha enviado la señal 14 %d veces\n", contador14);
    } else if (signum == 15) {
        contador15++;
        printf("Se ha enviado la señal 15 %d veces\n", contador15);
    } else {
        printf("No reconozco la señal enviada");
    }
}

int main(int argc, char** argv) {
    struct sigaction sig;

    printf("No puedo manejar la señal 9\n");

    if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf");
    }

    sig.sa_handler = handler;
    sigemptyset(&sig.sa_mask);

    if(sigaction(1, &sig, NULL) < 0) {
        perror("Señal");
    }
    if(sigaction(2, &sig, NULL) < 0) {
        perror("Señal");
    }
    if(sigaction(3, &sig, NULL) < 0) {
        perror("Señal");
    }
    if(sigaction(6, &sig, NULL) < 0) {
        perror("Señal");
    }
    if(sigaction(14, &sig, NULL) < 0) {
        perror("Señal");
    }
    if(sigaction(15, &sig, NULL) < 0) {
        perror("Señal");
    }


    for(;;){}
}