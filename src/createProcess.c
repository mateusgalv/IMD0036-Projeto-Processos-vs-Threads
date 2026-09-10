#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <sys/types.h>

void createProcess(int n) {
    struct timespec processStart, processEnd;
    long long time;

    pid_t pid = fork();

    if (pid == 0) {
        // PROCESSO FILHO
        clock_gettime(CLOCK_MONOTONIC, &processStart);
    } else {
        // PROCESSO PAI
        printf("Processo filho %d - Intervalo []\n", n);
    }

}