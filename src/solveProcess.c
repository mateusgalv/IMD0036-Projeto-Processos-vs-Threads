#define _POSIX_C_SOURCE 199309L

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>
#include "Configs.h"
#include "Results.h"
#include "ceilDivision.h"
#include "createProcess.h"
#include "readTempFiles.h"

void solveProcess(
    Configs *config,
    Results *result
){
    // SOLUÇÃO POR BLOCO
    if (strcmp(config->particao, "bloco") == 0) {
        long long blockStart, blockEnd, blockSize;
        long long ceil = config->b;
        
        blockSize = ceilDivision(result->length, config->w);
        blockStart = config->a;
        blockEnd = (config->a + blockSize - 1);

        printf(" ----> Solução por Processos + Blocos\n");
        printf(" ---> Tamanho dos blocos = %lld\n", blockSize);

        for(int i = 0; i < config->w; i++) {
            createProcess(i, blockStart, blockEnd, 1);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > ceil) blockEnd = ceil;
        }        
    }
    // SOLUÇÃO CÍCLICA
    else if (strcmp(config->particao, "ciclico") == 0) {
        printf(" ----> Solução por Processos + Ciclico");
        printf(" ---> Incremento = %d\n", config->w);

        for (int i = 0; i < config->w; i++) {
            createProcess(i, config->a + i, config->b, config->w);
        }
    }

    // ESPERA TODOS PROCESSOS FILHOS FINALIZAREM
    for (int j = 0; j < config->w; j ++) {
        wait(NULL);
    }
    // TIMER DE AGREGAÇÃO START
    clock_gettime(CLOCK_MONOTONIC, &result->aggregationTime.start);

    long long times[config->w];
    readTempFiles(config->w, times);

    long long maxTime = times[0];
    long long minTime = times[0];
    for (int k = 1; k < config->w; k++) {
        if (times[k] > maxTime) 
            maxTime = times[k];
        if (times[k] < minTime)
            minTime = times[k];
    }

    result->maxTime = maxTime;
    result->minTime = minTime;

    return;
}