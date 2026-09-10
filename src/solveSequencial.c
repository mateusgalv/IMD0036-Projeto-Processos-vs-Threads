#define _POSIX_C_SOURCE 199309L


#include <stdio.h>
#include <time.h>
#include <stepsCount.h>
#include <timer.h>
#include <createFile.h>
#include "InputData.h"

void solveSequencial(
    InputData input,
    struct timespec start
){
    long long time, steps = 0;
    struct timespec end;

    printf(" --> Execução sequencial (w = 1)\n");

    for(long long i = input.a; i <= input.b; i++) {
        steps += stepsCount(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time = timer(&start, &end);

    printf("Numero de passos: %lld, Tempo: %lld s ou %.2e s\n", steps, time, (double)time);

    // createOutputFile("-1", "sequencial", w, l, time, "-1", "-1", "-1", "sequencial");

    return;
}