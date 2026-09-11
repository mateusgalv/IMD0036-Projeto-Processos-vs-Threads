#include <time.h>

// Retorna tempo em nanossegundos
long long timer(
    struct timespec *start,
    struct timespec *end
){
    if (start == NULL) return -1;
    long long time = ((end->tv_sec - start->tv_sec) * 1000000000LL + 
        (end->tv_nsec - start->tv_nsec));

    return time;
}