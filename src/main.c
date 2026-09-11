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
    
    // TIMER & AGREGAÇÃO END
    clock_gettime(CLOCK_MONOTONIC, &end);
    output.time = timer(&start, &end);
    output.aggregationTime = timer(&input.aggregationStart, &end);

    createFile(&output, input.fileName);

    return 0;
}