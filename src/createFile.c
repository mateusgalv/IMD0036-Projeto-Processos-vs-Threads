#include <stdio.h>

void createFile(
    char fileName,
    char modo,
    char particao,
    int w,
    long long l,
    long long time,
    char maxTime,
    char minTime,
    char aggregationTime
){
    char path[32];

    snprintf(path, sizeof(path), "output/%s.txt", fileName);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) return;
    
    /*
    modo, particao,W,L,tempo_total,tempo_max_filho,tempo_min_filho,tempo_agregacao
    */
    fprintf(
        file,
        "%s,%s,%d,%lld",
        modo, particao, w, l, time, maxTime, minTime, aggregationTime
    );

    return;
}