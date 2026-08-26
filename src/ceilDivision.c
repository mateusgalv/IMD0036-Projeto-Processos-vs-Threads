#include <stdint.h>

#include "ceilDivision.h"

int64_t ceilDivision(int64_t l, int w) {
    return (l + w - 1)/w;
}