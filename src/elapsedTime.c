#include <time.h>

// Retorno em nsec
long long elapsedTime(
    struct timespec *start,
    struct timespec *end
){
    // if (start->tv_sec == 0 && start->tv_nsec == 0) return -1;
    
    long long secs = end->tv_sec - start->tv_sec;
    long long nsecs = end->tv_nsec - start->tv_nsec;
    
    if (nsecs < 0) {
        secs--;
        nsecs += 1000000000LL;
    }
    
    if (secs + nsecs == 0) return -1;

    return secs * 1000000000LL + nsecs;
}