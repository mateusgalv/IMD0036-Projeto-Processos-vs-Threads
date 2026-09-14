#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "Timer.h"
#include "stepsCount.h"
#include "elapsedTime.h"
#include "createTempFile.h"

void createProcess(
    int processId,
    long long start,
    long long end,
    int increment
){
    Timer processTime;

    pid_t pid = fork();
    if (pid < 0) {
        printf("fork %d falhou", processId);
        exit(1);
    }

    if (pid == 0) { // PROCESSO FILHO
        // TIMER START
        clock_gettime(CLOCK_MONOTONIC, &processTime.start);

        long long steps = 0;
        for (long long i = start; i <= end; i += increment) {
            steps += stepsCount(i);
        }
        
        // TIMER END
        clock_gettime(CLOCK_MONOTONIC, &processTime.end);
        long long elapsed = elapsedTime(&processTime.start, &processTime.end);
        printf(" -> Processo filho %d terminou - Passos = %lld | Tempo: %.2e ns\n", processId, steps, (double)elapsed);

        createTempFile(processId, elapsed);

        exit(0);
    } else { // PROCESSO PAI
        printf(" --> Processo filho %d criado - Intervalo [%lld, %lld]\n", processId, start, end);
    }
}