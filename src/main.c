#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "InputData.h"
#include "OutputData.h"
#include "timer.h"
#include "solveSequencial.h"
#include "solveProcess.h"
#include "solveThreads.h"
#include "createFile.h"

/*
./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
            1   2   3    4         5             6
*/
int main(int argc, char *argv[]) {
    (void)argc;
    struct timespec start, end;
    InputData input;
    OutputData output;

    input.a = strtoll(argv[1], NULL, 10);
    input.b = strtoll(argv[2], NULL, 10);
    input.w = atoi(argv[3]);
    output.length = (input.b - input.a + 1);
    output.w = input.w;
    
    // TIMER START
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (input.w == 1) {
        solveSequencial(&input, &output);
    } else {
        strcpy(input.modo, argv[4]);
        strcpy(output.modo, argv[4]);
        strcpy(input.particao, argv[5]);
        strcpy(output.particao, argv[5]);
        strcpy(input.fileName, argv[6]);
    }
    
    if (strcmp(input.modo, "processo") == 0) {
        solveProcess(&input, &output);
    } else if (strcmp(input.modo, "thread") == 0) {
        solveThreads(&input, &output);
    }

    // TIMER END
    clock_gettime(CLOCK_MONOTONIC, &end);
    output.time = timer(&start, &end);

    output.aggregationTime = timer(&input.aggregationStart, &end);

    createFile(&output, input.fileName);

    // IMPRIME RESULTADO
    printf("\nResultado = {\n");
    printf("  modo: %s,\n  particao: %s,\n", output.modo, output.particao);
    printf("  W: %d,\n  L: %lld,\n", output.w, output.length);
    printf("  tempo (s): %.2e,\n", (double)((output.time)/1000000000LL));
    printf("  maxTime (s): %.2e,\n", (double)((output.maxTime)/1000000000LL));
    printf("  minTime (s): %.2e,\n", (double)((output.minTime)/1000000000LL));
    printf("  aggregationTime (s): %.2e\n}", (double)((output.aggregationTime)/1000000000LL));
    return 0;
}