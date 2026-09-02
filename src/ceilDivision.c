#include <stdint.h>

#include "ceilDivision.h"

long long ceilDivision(long long l, int w) {
    return (l + w - 1)/w;
}