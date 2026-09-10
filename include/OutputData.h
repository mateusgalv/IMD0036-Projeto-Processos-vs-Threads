#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

typedef struct {
    char modo[32];
    char particao[32];
    int w;
    long long length;
    long long time;
    long long maxTime;
    long long minTime;
    long long aggregationTime;
} OutputData;

#endif