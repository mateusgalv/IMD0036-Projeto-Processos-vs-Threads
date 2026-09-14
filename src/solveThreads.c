#define _POSIX_C_SOURCE 199309L

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Configs.h"
#include "Results.h"
#include "ceilDivision.h"
#include "ThreadArgs.h"
#include "useThread.h"

void solveThreads(
    Configs *config,
    Results *result
){
    pthread_t threads[config->w];
    ThreadArgs args[config->w];

    // SOLUÇÃO POR BLOCOS
    if (strcmp(config->particao, "bloco") == 0) {
        long long blockSize, blockStart, blockEnd;
        blockSize = ceilDivision(result->length, config->w);
        blockStart = config->a;
        blockEnd = (config->a + blockSize - 1);

        printf(" ----> Solução por Threads + Blocos\n");
        printf(" ---> Tamanho dos blocos = %lld\n", blockSize);

        for (int i = 0; i < config->w; i++) {
            args[i].threadId = i;
            args[i].start = blockStart;
            args[i].end = blockEnd;
            args[i].increment = 1;

            pthread_create(&threads[i], NULL, useThread, &args[i]);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > config->b) blockEnd = config->b;
        }
    }
    // SOLUÇÃO CÍCLICA
    else if (strcmp(config->particao, "ciclico") == 0) {
        printf(" ----> Solução por Threads + Ciclico");
        printf(" ---> Incremento = %d\n", config->w);

        for (int i = 0; i < config->w; i++) {
            args[i].threadId = i;
            args[i].start = config->a + i;
            args[i].end = config->b;
            args[i].increment = config->w;

            pthread_create(&threads[i], NULL, useThread, &args[i]);
        }
    }

    // ESPERA TODAS THREADS FINALIZAREM
    for (int j = 0; j < config->w; j ++) {
        pthread_join(threads[j], NULL);
    }
    
    // TIMER DE AGREGAÇÃO START
    clock_gettime(CLOCK_MONOTONIC, &result->aggregationTime.start);

    long long maxTime = args[0].time;
    long long minTime = args[0].time;
    for (int k = 1; k < config->w; k++) {
        if (args[k].time > maxTime) 
            maxTime = args[k].time;
        if (args[k].time < minTime)
            minTime = args[k].time;
    }

    result->maxTime = maxTime;
    result->minTime = minTime;

    return;
}