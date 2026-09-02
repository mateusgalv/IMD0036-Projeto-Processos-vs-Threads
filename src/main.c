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
#include <pthread.h>

#include "isEven.h"
#include "stepsCount.h"
#include "ceilDivision.h"
#include "intervalCount.h"
#include "timer.h"

// MATRICULA = 007273;
// A = 100.007.273 -> B = 8.000.000.000

typedef struct {
    int id;
    long long start;
    long long end;
    long long *threadTime;
} ThreadArgs;

void report(const int id, const long long *steps, const long long *time) {
    char path[32];
    
    snprintf(path, sizeof(path), "temp/parcial_%d.txt", id);
    
    FILE *file = fopen(path, "w");

    if (file == NULL) exit(-1);

    fprintf(file, "%lld %lld\n", *steps, *time);

    fclose(file);
}

void createOutputFile(const char *modo,
    const char *particao,
    const int w,
    const long long l,
    const char *time,
    const char *maxTime,
    const char *minTime,
    const char *agregationTime,
    const char *fileName
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

void createTempFile(const int id, long long steps, long long time) {
    char path[32];

    snprintf(path, sizeof(path), "temp/parcial_%d.txt", id);
    
    FILE *file = fopen(path, "w");
    if (file == NULL) exit(-1);
    
    fprintf(file,"%lld,%.2e", steps, (double)time);

    fclose(file);
}

void createProcess(const int id, const long long start, const long long end) {
    struct timespec timerStart, timerEnd;
    long long processTotalTime, i, steps = 0;

    pid_t pid = fork(); 
    
    if(pid == 0) {
        // PROCESSO FILHO
        clock_gettime(CLOCK_MONOTONIC, &timerStart);
        for(i = start; i <= end; i++) {
            steps += stepsCount(i);
        }
        printf("Filho %d terminou, %lld passos\n", id, steps);
        
        clock_gettime(CLOCK_MONOTONIC, &timerEnd);
        processTotalTime = timer(&timerStart, &timerEnd);
        createTempFile(id, steps, processTotalTime);
        printf("Tempo do filho %d: %lld segundos ou %.2e segundos\n", id, processTotalTime, (double)processTotalTime);

        exit(1);
    } else {
        // PROCESSO PAI
        printf(" --> Filho %d criado (PID: %d), [%lld, %lld]\n", id, pid, start, end);
    }
}

void *useThread(void *arg) {
    struct timespec timerStart, timerEnd;
    long long threadTotalTime, steps = 0;

    ThreadArgs *args = arg;

    clock_gettime(CLOCK_MONOTONIC, &timerStart);

    for(int i = args->start; i <= args->end; i++) {
        steps += stepsCount(i);
    }
    printf("Thread %d terminou, %lld passos\n", args->id, steps);

    clock_gettime(CLOCK_MONOTONIC, &timerEnd);

    threadTotalTime = timer(&timerStart, &timerEnd);
    args->threadTime[args->id] = threadTotalTime;

    printf("Tempo da thread %d: %lld segundos ou %.2e segundos\n", args->id, threadTotalTime, (double)threadTotalTime);
    return NULL;
}


/*
./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
            1   2   3    4         5             6
*/
int main(int argc, char *argv[]) {
    (void)argc;

    int w;
    long long a, b, l, time, maxTime, minTime; 
    // aggregationTime;
    struct timespec start, end, aggregationStart, aggregationEnd;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    a = strtoll(argv[1], NULL, 10);
    b = strtoll(argv[2], NULL, 10);
    w = strtoll(argv[3], NULL, 10);
    
    l = b - a + 1;

    pthread_t threads[w];
    long long threadTime[w];
    ThreadArgs args[w];

    printf(" -> Intervalo [%lld,%lld]\n -> L = %lld\n", a, b, l);

    // SEQUENCIAL
    if (w == 1) {
        char timeStr[32];

        printf(" --> Execução sequencial (w = 1)\n");
        
        for(long long i = a; i <= b; i++) {
            stepsCount(i);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        time = timer(&start, &end);
        snprintf(timeStr, sizeof(timeStr), "%.2e", (double)time);
        
        printf("Tempo: %lld s ou %.2e s\n", time, (double)time);

        createOutputFile("-1", "sequencial", w, l, timeStr, "-1", "-1", "-1", "sequencial");

        return 0;
    } 

    // LOGICA POR BLOCOS - PROCESSOS OU THREADS
    if (strcmp(argv[5], "bloco") == 0) {
        long long blockSize, blockStart, blockEnd;

        blockSize = ceilDivision(l, w);
        printf(" -> Tamanho dos blocos = %lld\n", blockSize);
        blockStart = a;
        blockEnd = a + blockSize - 1;

        for(int i = 0; i < w; i++) {
            if (strcmp(argv[4], "processo") == 0) {
                createProcess(i, blockStart, blockEnd);
            } else if (strcmp(argv[4], "thread") == 0) {
                args[i].id = i;
                args[i].start = blockStart;
                args[i].end = blockEnd;
                args[i].threadTime = threadTime;

                pthread_create(&threads[i], NULL, useThread, &args[i]);
            }

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > b) blockEnd = b;
        }

        for(int i = 0; i < w; i++) {
            if (strcmp(argv[4], "processo") == 0)
                wait(NULL);
            if (strcmp(argv[4], "thread") == 0)
                pthread_join(threads[i], NULL);
        }
        clock_gettime(CLOCK_MONOTONIC, &aggregationStart);
        
        for(int i = 0; i < w; i++) {
            if (strcmp(argv[4], "processo") == 0) {
                // LER ARQUIVOS
                // GERAR ARQUIVO FINAL
            }
            if (strcmp(argv[4], "thread") == 0) {
                printf("Thread %d -> Tempo: %.2e\n", i, (double)threadTime[i]);

                maxTime = threadTime[0];
                minTime = threadTime[0];

                for (int j = 1; j < w; j++) {
                    if(maxTime < threadTime[j]) maxTime = threadTime[j];
                    if(minTime > threadTime[j]) minTime = threadTime[j];
                }
            }
        }

        clock_gettime(CLOCK_MONOTONIC, &aggregationEnd);
        clock_gettime(CLOCK_MONOTONIC, &end);
        // aggregationTime = timer(&aggregationStart, &aggregationEnd);
        time = timer(&start, &end);
        
        // createOutputFile(argv[4], argv[5], w, l, &time, &maxTime, &minTime, &aggregationTime, argv[6]);

    // PROCESSOS
    /*

    if (strcmp(argv[4], "processo") == 0) {
              
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
   
    */
    }
    
    // LOGICA CICLICA - PROCESSOS OU THREADS
    
    return 0;
}