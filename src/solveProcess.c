#define _POSIX_C_SOURCE 199309L

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>

#include "InputData.h"
#include "OutputData.h"
#include "createProcess.h"
#include "ceilDivision.h"
#include "readTempFiles.h"

void solveProcess(
    InputData *input,
    OutputData *output
){
    // SOLUÇÃO POR BLOCO
    if (strcmp(input->particao, "bloco") == 0) {
        long long blockSize, blockStart, blockEnd;
        blockSize = ceilDivision(output->length, input->w);
        blockStart = input->a;
        blockEnd = (input->a + blockSize - 1);

        printf(" --> Solução por Processos + Blocos - Tamanho dos blocos = %lld\n", blockSize);

        for(int i = 0; i < input->w; i++) {
            createProcess(i, blockStart, blockEnd, 1);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > input->b) blockEnd = input->b;
        }        
    }
    // SOLUÇÃO CÍCLICA
    else if (strcmp(input->particao, "ciclico") == 0) {
        printf(" --> Solução por Processos + Ciclico, Incremento = %d\n", input->w);

        for (int i = 0; i < input->w; i++) {
            createProcess(i, input->a + i, input->b, input->w);
        }
    }

    for (int j = 0; j < input->w; j ++) {
        // Espera todos os filhos
        wait(NULL);
    }

    // TIMER DE AGREGAÇÃO START
    clock_gettime(CLOCK_MONOTONIC, &input->aggregationStart);

    long long times[input->w];
    readTempFiles(input->w, times);
    long long maxTime = times[0];
    long long minTime = times[0];
    for (int k = 1; k < input->w; k++) {
        if (times[k] > maxTime) 
            maxTime = times[k];
        if (times[k] < minTime)
            minTime = times[k];
    }

    output->maxTime = maxTime;
    output->minTime = minTime;
    printf("maxTime (ns) = %lld, minTime (ns) = %lld\n", maxTime, minTime);

    return;
}