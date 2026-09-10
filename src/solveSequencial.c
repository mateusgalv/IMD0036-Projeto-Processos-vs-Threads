#define _POSIX_C_SOURCE 199309L

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stepsCount.h>
#include <timer.h>
#include <createFile.h>
#include "InputData.h"
#include "OutputData.h"

void solveSequencial(
    InputData *input,
    OutputData *output,
    struct timespec start
){
    long long time, steps = 0;
    struct timespec end;

    printf(" --> Execução sequencial (w = 1)\n");

    for(long long i = input->a; i <= input->b; i++) {
        steps += stepsCount(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    time = timer(&start, &end);

    printf("Numero de passos: %lld, Tempo: %lld segundos (%.2e segundos)\n", steps, time, (double)time);

    strcpy(input->fileName, "sequencial");

    strcpy(output->modo, "sequencial");
    strcpy(output->particao, "bloco");
    output->w = input->w;
    output->length = (input->b - input->a + 1);
    output->time = time;
    output->maxTime = -1;
    output->minTime = -1;
    output->aggregationTime = -1;

    return;
}