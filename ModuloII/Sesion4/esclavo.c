/**
 * @file esclavo.c
 * @author Alejandro Rubio Martinez (you@domain.com)
 * @brief Calcula los primos dado un intervalo
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char**argv) {
    int min, max;
    char ret[500], temp[10];

    min = atoi(argv[1]);
    max = atoi(argv[2]);
    sprintf(ret,"");

    for (int i = min; i <= max; i++) {
        for (int j = 2; j <= i/2+1; j++) {
            if (j == i/2+1) {
                write(STDOUT_FILENO, &i, sizeof(int));
            }
            if (i%j == 0)
                break;
        }
    }

    printf("%s\n", ret);

    return 0;
}