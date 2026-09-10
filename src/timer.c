#include <time.h>

// Retorna tempo em nanossegundos
long long timer(const struct timespec *start, const struct timespec *end) {
    long long time = ((end->tv_sec - start->tv_sec) * 1000000000LL + 
        (end->tv_nsec - start->tv_nsec));

    return time;
}