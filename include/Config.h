#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    long long a;
    long long b;
    long long length;
    int w;
    char modo[32];
    char particao[32];
    char fileName[32];
} Config;

#endif