#include <stdio.h>
#include "OutputData.h"

// modo,particao,W,L,tempo_total,tempo_max_filho,tempo_min_filho,tempo_agregacao
void createFile(
    OutputData output
){
    char path[32];

    snprintf(path, sizeof(path), "output/%s.txt", "fileName");
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    
    // fprintf(
    //     file,
    //     "%s,%s,%d,%lld",
    //     modo, particao, w, l, time, maxTime, minTime, aggregationTime
    // );

    return;
}