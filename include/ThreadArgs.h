#ifndef THREADARGS_H
#define THREADARGS_H

typedef struct {
    int threadId;
    long long start;
    long long end;
    long long time;
    int increment;
} ThreadArgs;

#endif