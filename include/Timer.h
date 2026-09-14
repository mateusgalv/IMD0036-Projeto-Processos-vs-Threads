#ifndef TIMES_H
#define TIMES_H

#include <time.h>

typedef struct {
    struct timespec start;
    struct timespec end;
} Timer;

#endif