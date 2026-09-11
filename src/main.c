#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>


#include "isEven.h"
#include "stepsCount.h"
#include "ceilDivision.h"
#include "intervalCount.h"
#include "timer.h"
#include "InputData.h"
#include "OutputData.h"
#include "createFile.h"
#include "solveSequencial.h"
#include "solveProcess.h"
#include "solveThreads.h"

// MATRICULA = 007273;
// A = 100.007.273 -> B = 8.000.000.000

void report(const int id, const long long *steps, const long long *time) {
    char path[32];
    
    snprintf(path, sizeof(path), "temp/parcial_%d.txt", id);
    
    FILE *file = fopen(path, "w");

    if (file == NULL) exit(-1);

    fprintf(file, "%lld %lld\n", *steps, *time);

    fclose(file);
}

/*
./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
            1   2   3    4         5             6
*/
int main(int argc, char *argv[]) {
    (void)argc;
    struct timespec start, end;
    InputData input;
    OutputData output;

    // TIMER START
    clock_gettime(CLOCK_MONOTONIC, &start);

    input.a = strtoll(argv[1], NULL, 10);
    input.b = strtoll(argv[2], NULL, 10);
    input.w = atoi(argv[3]);
    
    if (input.w == 1) {
        solveSequencial(&input, &output, start);
    } else {
        strcpy(input.modo, argv[4]);
        strcpy(output.modo, argv[4]);
        strcpy(input.particao, argv[5]);
        strcpy(output.particao, argv[5]);
        strcpy(input.fileName, argv[6]);
        output.length = (input.b - input.a + 1);
    }
    
    if (strcmp(argv[4], "processo") == 0) {
        solveProcess(&input, &output);
    } else { // threads
        solveThreads(&input, &output);
    }
    
    // LOGICA POR BLOCOS - PROCESSOS OU THREADS
    // if (strcmp(argv[5], "bloco") == 0) {
    //     long long blockSize, blockStart, blockEnd;

    //     blockSize = ceilDivision(l, w);
    //     printf(" -> Tamanho dos blocos = %lld\n", blockSize);
    //     blockStart = a;
    //     blockEnd = a + blockSize - 1;

    //     for(int i = 0; i < w; i++) {
    //         if (strcmp(argv[4], "processo") == 0) {
    //             createProcess(i, blockStart, blockEnd);
    //         } else if (strcmp(argv[4], "thread") == 0) {
    //             args[i].id = i;
    //             args[i].start = blockStart;
    //             args[i].end = blockEnd;
    //             args[i].threadTime = threadTime;

    //             pthread_create(&threads[i], NULL, useThread, &args[i]);
    //         }

    //         blockStart = blockEnd + 1;
    //         blockEnd = blockEnd + blockSize;
    //         if (blockEnd > b) blockEnd = b;
    //     }

    //     for(int i = 0; i < w; i++) {
    //         if (strcmp(argv[4], "processo") == 0)
    //             wait(NULL);
    //         if (strcmp(argv[4], "thread") == 0)
    //             pthread_join(threads[i], NULL);
    //     }
    //     clock_gettime(CLOCK_MONOTONIC, &aggregationStart);
        
    //     for(int i = 0; i < w; i++) {
    //         if (strcmp(argv[4], "processo") == 0) {
    //             // LER ARQUIVOS
    //             // GERAR ARQUIVO FINAL
    //         }
    //         if (strcmp(argv[4], "thread") == 0) {
    //             printf("Thread %d -> Tempo: %.2e\n", i, (double)threadTime[i]);

    //             maxTime = threadTime[0];
    //             minTime = threadTime[0];

    //             for (int j = 1; j < w; j++) {
    //                 if(maxTime < threadTime[j]) maxTime = threadTime[j];
    //                 if(minTime > threadTime[j]) minTime = threadTime[j];
    //             }
    //         }
    //     }

    //     clock_gettime(CLOCK_MONOTONIC, &aggregationEnd);
    //     clock_gettime(CLOCK_MONOTONIC, &end);
    //     aggregationTime = timer(&aggregationStart, &aggregationEnd);
    //     time = timer(&start, &end);
        
    //     char maxTimeStr[64], minTimeStr[64], aggregationTimeStr[64];

    //     snprintf(maxTimeStr, sizeof(maxTimeStr), "%.2e", (double)maxTime);
    //     snprintf(minTimeStr, sizeof(minTimeStr), "%.2e", (double)minTime);
    //     snprintf(aggregationTimeStr, sizeof(aggregationTimeStr), "%.2e", (double)aggregationTime);
    //     createOutputFile(argv[4], argv[5], w, l, time, maxTimeStr, minTimeStr, aggregationTimeStr, argv[6]);
    
    // }
    
    // TIMER & AGREGAÇÃO END
    clock_gettime(CLOCK_MONOTONIC, &end);
    output.time = timer(&start, &end);
    output.aggregationTime = timer(&input.aggregationStart, &end);

    createFile(&output, input.fileName);

    return 0;
}