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
    OutputData *output
){
    long long steps = 0;

    printf(" --> Execução sequencial (w = 1)\n");

    for(long long i = input->a; i <= input->b; i++) {
        steps += stepsCount(i);
    }

    struct timespec aggregationTime = {0};
    input->aggregationStart = aggregationTime;
   
    return;
}