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
    printf("  tempo (ns): %.2e,\n", (double)result->totalTime);
    printf("  maxTime (s): %.2e,\n", (double)result->maxTime);
    printf("  minTime (s): %.2e,\n", (double)result->minTime);
    printf("  aggregationTime (s): %.2e\n}\n", (double)result->aggTime);
}