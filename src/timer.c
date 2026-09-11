#include <time.h>

// Retorna tempo em nanossegundos
long long timer(
    struct timespec *start,
    struct timespec *end
){
    if (start->tv_sec == 0 && start->tv_nsec == 0) return -1;
    
    long long time = ((end->tv_sec - start->tv_sec) * 1000000000LL + 
        (end->tv_nsec - start->tv_nsec));

    return time;
}