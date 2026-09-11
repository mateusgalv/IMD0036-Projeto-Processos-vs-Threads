#include <stdio.h>
#include "OutputData.h"

// modo,particao,W,L,tempo_total,tempo_max_filho,tempo_min_filho,tempo_agregacao
void createFile(
    OutputData *output,
    char *fileName
){
    char path[32];

    snprintf(path, sizeof(path), "output/%s.txt", fileName);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    fprintf(
        file,
        "%s,%s,%d,%lld,%lld,%lld,%lld,%lld",
        output->modo,
        output->particao,
        output->w,
        output->length,
        output->time,
        output->maxTime,
        output->minTime,
        output->aggregationTime
    );

    fclose(file);
    return;
}