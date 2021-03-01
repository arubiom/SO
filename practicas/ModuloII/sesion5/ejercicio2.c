#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int senales[31];

void sig_usr_hndl(int i) {
    senales[i]++;
}

int main() {

    struct sigaction sig_USR_nact;

    for (int i = 0; i < 31; i++) {
        senales[i] = 0;
    }

    if (setvbuf(stdout, NULL, _IONBF, 0)) {
        perror("Error al vaciar el buffer");
    }

    sig_USR_nact.sa_handler = sig_usr_hndl;
    sig_USR_nact.sa_flags = 0;
    sigemptyset(&sig_USR_nact.sa_mask);

    for (int i = 1; i < 31 && i != SIGSTOP && i != SIGKILL; i++) {
        if (sigaction(i, &sig_USR_nact, NULL) == -1)
            printf("Señal desconocida %i\n", i);
    }

    while(1);

}