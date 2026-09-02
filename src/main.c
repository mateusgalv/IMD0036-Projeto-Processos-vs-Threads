#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "isEven.h"
#include "stepsCount.h"
#include "ceilDivision.h"
#include "intervalCount.h"
#include "timer.h"

// MATRICULA = 007273;
// A = 100.007.273 -> B = 8.000.000.000

void report(const int id, const long long *steps, const long long *time) {
    char path[32];
    
    snprintf(path, sizeof(path), "temp/parcial_%d.txt", id);
    
    FILE *file = fopen(path, "w");

    if (file == NULL) exit(-1);

    fprintf(file, "%lld %lld\n", *steps, *time);

    fclose(file);
}

void createOutputFile(const char modo,
    const char particao,
    const int w,
    const long long l,
    const char time,
    const char maxTime,
    const char minTime,
    const char agregationTime,
    const char fileName
) {
    char path[32];

    snprintf(path, sizeof(path), "output/%s.txt", fileName);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) exit(-1);
    
    fprintf(file,
        "%s,%s,%d,%lld,%s,%s,%s,%s\n",
        modo, particao, w, l, time, maxTime, minTime, agregationTime
    );

    fclose(file);
}

/*
./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
            1   2   3    4         5             6
*/
int main(int argc, char *argv[]) {
    (void)argc;

    long long a, b, l, time;
    int w;
    struct timespec start, end;
    char timeStr[32];

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    a = strtoll(argv[1], NULL, 10);
    b = strtoll(argv[2], NULL, 10);
    w = strtoll(argv[3], NULL, 10);
    l = b - a + 1;

    printf(" -> Intervalo [%lld,%lld]\n -> L = %lld\n", a, b, l);

    // SEQUENCIAL
    if (w == 1) {
        printf(" --> Execução sequencial (w = 1)\n");
        
        for(long long i = a; i <= b; i++) {
            stepsCount(i);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        time = timer(&start, &end);
        snprintf(timeStr, sizeof(timeStr), "%.2e", (double)time);
        
        // printf("Tempo: %lld ns ou %.2e s\n", time, (double)time);
        
        // sequencial,-1,w,l,timeStr,-1,-1,-1
        // criar arquivo

        return 0;
    } 

    // PROCESSOS
    if (strcmp(argv[4], "processo") == 0) {
        
        // BLOCO
        if (strcmp(argv[5], "bloco")== 0) {
            long long length, blockSize, blockStart, blockEnd, steps;
            
            length = b - a + 1;
            blockSize = ceilDivision(length, w);
            printf(" -> Tamanho dos blocos = %lld\n", blockSize);

            blockStart = a;
            blockEnd = a + blockSize;

            for(int i = 0; i < w; i++) {
                pid_t pid = fork();
                if (pid != 0) printf(" --> Filho %d - PID: %d criado\n", i, pid);
        
                if (pid == 0) {
                    // PROCESSO FILHO
                    struct timespec start, end;
                    long long time;

                    // -----> CONTAGEM DE TEMPO INICIO
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    
                    // -----> CONTAGEM DE PASSOS 
                    steps = intervalCount(blockStart, blockEnd);
                    printf(" ---> Filho %d -> [%lld, %lld] -> %lld passos\n", i, blockStart, blockEnd, steps);
                
                    // -----> CONTAGEM DE TEMPO FIM
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    time = timer(&start, &end);
                    printf(" ---> Filho %d -> TEMPO: %lld nanosegundos\n", i, time);
                    
                    // -----> ESCREVER ARQUIVO
                    report(i, &steps, &time);

                    exit(0);               
                }

                blockStart = blockEnd + 1;
                blockEnd = blockEnd + blockSize;
                if (blockEnd > b) blockEnd = b;
            }

            // PROCESSO PAI
            for(int j = 0; j < w; j++) {
                // -----> ESPERA OS FILHOS ENCERRAREM
                wait(NULL);
            }


        }
        
        // CICLICO
        if (strcmp(argv[5], "ciclico")== 0) {
            
            for(int i = 0; i < w; i++) {
                pid_t pid = fork();
                if (pid != 0) printf(" --> Filho %d - PID: %d criado\n", i, pid);

                if (pid == 0) {
                    // PROCESSO FILHO
                    struct timespec start, end;
                    long long steps = 0, time;

                    // -----> CONTAGEM DE TEMPO INICIO
                    clock_gettime(CLOCK_MONOTONIC, &start);

                    // -----> CONTAGEM DE PASSOS
                    for(long long number = i + a; number <= b; number += w) {
                        steps += stepsCount(number);
                    }
                    printf(" ---> Filho %d -> Passos = %lld\n", i, steps);
                    
                    // -----> CONTAGEM DE TEMPO FIM
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    time = timer(&start, &end);
                    printf(" ---> Filho %d -> TEMPO: %lld nanosegundos\n", i, time);
                    
                    // -----> ESCREVER ARQUIVO
                    report(i, &steps, &time);

                    exit(0);
                }
            }
        }
    } 
    
    // THREADS
    if (strcmp(argv[4], "thread") == 0) {}

    return 0;
}