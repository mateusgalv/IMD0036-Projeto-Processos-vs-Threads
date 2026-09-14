#include <stdio.h>

void createTempFile(
    int processId,
    long long time
){
    char path[32];

    snprintf(path, sizeof(path), "temp/parcial_%d.txt", processId);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    fprintf(file, "%lld", time);

    fclose(file);
    return;
}