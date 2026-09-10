
#include <pthread.h>

#include "InputData.h"
#include "OutputData.h"
#include "ceilDivision.h"

typedef struct {
    int threadId;
    long long start;
    long long end;
    long long time;
} ThreadArgs;

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

            // pthread_create(&threads[i], NULL, useThread, &args[i]);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > input->b) blockEnd = input->b;
        }
    }
    // SOLUÇÃO CÍCLICA
    else if (strcmp(input->particao, "ciclico") == 0) {
        printf(" --> Solução por Threads + Ciclico - Incremento = %lld\n", input->w);

    }

    for (int j = 0; j < input->w; j ++) {
        // Espera todas as threads
        pthread_join(threads[j], NULL);
    }
}