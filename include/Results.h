#ifndef RESULTS_H
#define RESULTS_H

#include "Timer.h"

typedef struct {
    long long length;
    long long totalTime;
    long long maxTime;
    long long minTime;
    Timer aggregationTime;
    long long aggTime;
} Results;

#endif