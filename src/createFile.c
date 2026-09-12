#include <stdio.h>
#include "OutputData.h"

// modo,particao,W,L,tempo_total,tempo_max_filho,tempo_min_filho,tempo_agregacao
void createFile(
    OutputData *output,
    char *fileName
){
    char path[32];

    snprintf(path, sizeof(path), "output/%s", fileName);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    fprintf(
        file,
        "%s,%s,%d,%lld,%.2e,%.2e,%.2e,%.2e",
        output->modo,
        output->particao,
        output->w,
        output->length,
        (double)((output->time)/1000000000LL),
        (double)((output->maxTime)/1000000000LL),
        (double)((output->minTime)/1000000000LL),
        (double)((output->aggregationTime)/1000000000LL)
    );

    fclose(file);
    return;
}