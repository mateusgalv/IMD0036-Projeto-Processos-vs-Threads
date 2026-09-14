#define _POSIX_C_SOURCE 199309L

#include <string.h>
#include <stdio.h>
#include <stepsCount.h>
#include "Configs.h"
#include "Timer.h"

void solveSequencial(
    Configs *config
){
    long long steps = 0;

    printf(" --> Solução sequencial (w = 1)\n");

    for(long long i = config->a; i <= config->b; i++) {
        steps += stepsCount(i);
    }

    printf(" Passos = %lld\n", steps);

    return;
}