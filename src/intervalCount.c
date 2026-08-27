#include <stdint.h>

#include "stepsCount.h"

int64_t intervalCount(int64_t a, int64_t b) {
    int64_t count = 0;

    for(int64_t i = a; i <= b; i++) {
        count += stepsCount(i);
    }

    return count;
}