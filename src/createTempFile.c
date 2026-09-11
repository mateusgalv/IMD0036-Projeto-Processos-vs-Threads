#include <stdio.h>
#include "OutputData.h"

// steps,time
void createTempFile(
    int processId,
    long long steps,
    long long time
){
    char path[32];

    snprintf(path, sizeof(path), "temp/parcial_%d.txt", processId);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    fprintf(file, "%lld,%lld", steps, time);

    fclose(file);
    return;
}