#ifndef ELAPSEDTIME_H
#define ELAPSEDTIME_H

#include <time.h>

long long elapsedTime(
    struct timespec *start,
    struct timespec *end
);

#endif