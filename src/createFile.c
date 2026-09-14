#include <stdio.h>
#include "Configs.h"
#include "Results.h"

// modo,particao,W,L,tempo_total,tempo_max_filho,tempo_min_filho,tempo_agregacao
void createFile(
    Configs *config,
    Results *result
){
    char path[64];

    snprintf(path, sizeof(path), "output/%s", config->fileName);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    fprintf(
        file,
        "%s,%s,%d,%lld,%.2e,%.2e,%.2e,%.2e",
        config->modo,
        config->particao,
        config->w,
        result->length,
        (double)((result->totalTime)),
        (double)((result->maxTime)),
        (double)((result->minTime)),
        (double)((result->aggTime))
    );

    fclose(file);
    return;
}