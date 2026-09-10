#define _POSIX_C_SOURCE 199309L

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "InputData.h"
#include "OutputData.h"
#include "ceilDivision.h"
#include "ThreadArgs.h"
#include "useThread.h"

void solveThreads(
    InputData *input,
    OutputData *output
){
    pthread_t threads[input->w];
    ThreadArgs args[input->w];

    // SOLUÇÃO POR BLOCO
    if (strcmp(input->particao, "bloco") == 0) {
        long long blockSize, blockStart, blockEnd;
        output->length = (input->b - input->a - 1);
        blockSize = ceilDivision(output->length, input->w);
        blockStart = input->a;
        blockEnd = (input->a + blockSize - 1);

        printf(" --> Solução por Threads + Blocos - Tamanho dos blocos = %lld\n", blockSize);

        for (int i = 0; i < input->w; i++) {
            args[i].threadId = i;
            args[i].start = blockStart;
            args[i].end = blockEnd;
            args[i].increment = 1;

            pthread_create(&threads[i], NULL, useThread, &args[i]);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > input->b) blockEnd = input->b;
        }
    }
    // SOLUÇÃO CÍCLICA
    else if (strcmp(input->particao, "ciclico") == 0) {
        printf(" --> Solução por Threads + Ciclico - Incremento = %d\n", input->w);

        for (int i = 0; i < input->w; i++) {
            args[i].threadId = i;
            args[i].start = input->a + i;
            args[i].end = input->b;
            args[i].increment = input->w;

            pthread_create(&threads[i], NULL, useThread, &args[i]);
        }
    }

    for (int j = 0; j < input->w; j ++) {
        // Espera todas as threads
        pthread_join(threads[j], NULL);
    }
    // TIMER DE AGREGAÇÃO START
    clock_gettime(CLOCK_MONOTONIC, &input->aggregationStart);

    long long maxTime, minTime;
    maxTime = args[0].time;
    minTime = args[0].time;
    for (int k = 1; k < input->w; k++) {
        if (args[k].time > maxTime) 
            maxTime = args[k].time;
        if (args[k].time < minTime)
            minTime = args[k].time;
    }

    output->maxTime = maxTime;
    output->minTime = minTime;

    printf("maxTime (ns) = %lld, minTime (ns) = %lld\n", maxTime, minTime);
}