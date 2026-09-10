#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <time.h>

typedef struct {
    long long a;
    long long b;
    int w;
    char modo[32];
    char particao[32];
    char fileName[32];
    struct timespec aggregationStart;
} InputData;

#endif