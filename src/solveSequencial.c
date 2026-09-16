#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Configs.h"
#include "Results.h"
#include <stepsCount.h>

void solveSequencial(
    Configs *config,
    Results *result
){
    printf(" --> Solução sequencial (w = 1)\n");

    for(long long i = config->a; i <= config->b; i++) {
        stepsCount(i);
    }

    result->maxTime = -1;
    result->minTime = -1;
    result->aggTime = -1;

    strcpy(config->modo, "sequencial");
    strcpy(config->particao, "bloco");
    strcpy(config->fileName, "sequencial.txt");

    return;
}