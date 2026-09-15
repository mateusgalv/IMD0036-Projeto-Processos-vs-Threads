#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Configs.h"
#include "Results.h"
#include "Timer.h"

#include "elapsedTime.h"
#include "solveSequencial.h"
#include "solveProcess.h"
#include "solveThreads.h"
#include "createFile.h"
#include "printResult.h"

/*
./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
            1   2   3    4         5             6
*/
int main(int argc, char *argv[]) {
    (void)argc;
    Configs config;
    Results result;
    Timer totalTime;

    // COMENTARIOS PARA VIDEO:
    // Timer totalTime pode ser movido para Results
    // em Results temos um Timer para agg
    
    config.a = strtoll(argv[1], NULL, 10);
    config.b = strtoll(argv[2], NULL, 10);
    config.w = atoi(argv[3]);
    result.length = (config.b - config.a + 1);

    // TIMER START
    clock_gettime(CLOCK_MONOTONIC, &totalTime.start);

    if (config.w == 1) {
        solveSequencial(&config, &result);
    } else {
        strcpy(config.modo, argv[4]);
        strcpy(config.particao, argv[5]);
        strcpy(config.fileName, argv[6]);
    }
    
    if (strcmp(config.modo, "processo") == 0) {
        solveProcess(&config, &result);
    } 
    if (strcmp(config.modo, "thread") == 0) {
        solveThreads(&config, &result);
    }

    // TIMER END
    clock_gettime(CLOCK_MONOTONIC, &totalTime.end);
    result.totalTime = elapsedTime(&totalTime.start, &totalTime.end);
    if (config.w != 1) {
        result.aggTime = elapsedTime(&result.aggregationTime.start, &totalTime.end);
    }
    
    createFile(&config, &result);
    printResult(&config, &result);
    
    return 0;
}