#include <stdio.h>
#include <Configs.h>
#include <Results.h>

void printResult(
    Configs *config,
    Results *result
) {
    printf("\nResultado = {\n");
    printf("  modo: %s,\n", config->modo);
    printf("  particao: %s,\n", config->particao);
    printf("  W: %d,\n  L: %lld,\n", config->w, result->length);
    printf("  tempo (s): %.2e,\n", ((double)result->totalTime)/1000000000LL);
    printf("  maxTime (s): %.2e,\n", ((double)result->maxTime)/1000000000LL);
    printf("  minTime (s): %.2e,\n", ((double)result->minTime)/1000000000LL);
    printf("  aggregationTime (s): %.2e\n}\n", ((double)result->aggTime)/1000000000LL);
}