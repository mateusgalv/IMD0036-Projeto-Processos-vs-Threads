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

// MATRICULA = 007273;
// A = 100.007.273 -> B = 8.000.000.000

// ./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
int main(int argc, char *argv[]) {
    (void)argc;

    int64_t a, b, length, blockSize;
    int w;
    
    a = (int64_t)strtoll(argv[1], NULL, 10);
    b = (int64_t)strtoll(argv[2], NULL, 10);
    w = (int64_t)strtoll(argv[3], NULL, 10);

    printf(" -> Intervalo [%lld,%lld]\n", (long long)a, (long long)b);
    printf(" -> W = %d, Modo: %s, Particao: %s\n", w, argv[4], argv[5]);

    // SEQUENCIAL
    if (w == 1) {
        printf(" --> Execução sequencial:\n");
        
        for(int64_t i = a; i <= b; i++) {
            stepsCount(i);
        }

        return 0;
    } 

    // PROCESSOS OU THREADS

    if (strcmp(argv[4], "processo") == 0) {
        // PROCESSO
        
        if (strcmp(argv[5], "bloco")== 0) {
            // BLOCO

            length = b - a + 1;
            blockSize = ceilDivision(length, w);
            printf(" -> Tamanho dos blocos = %lld\n", (long long)blockSize);

            int64_t blockStart, blockEnd, steps;
            blockStart = a;
            blockEnd = a + blockSize;

            for(int j = 0; j < w; j++) {
                pid_t pid = fork();
                if (pid != 0) printf(" --> Filho %d - PID: %d criado\n", j, pid);
        
                if (pid == 0) {
                    // PROCESSO FILHO
                    struct timespec start, end;
                    int64_t elapsed;
                    
                    char path[32];

                    // -----> CONTAGEM DE TEMPO INICIO
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    
                    // -----> CONTAGEM DE PASSOS
                    steps = intervalCount(blockStart, blockEnd);
                    printf(" ---> Filho %d -> [%lld, %lld] -> %lld passos\n", j, (long long)blockStart, (long long)blockEnd, (long long)steps);
                
                    // -----> CONTAGEM DE TEMPO FIM
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    elapsed = (end.tv_sec - start.tv_sec) * INT64_C(1000000000) + 
                    (end.tv_nsec - start.tv_nsec);
                    printf(" ---> Filho %d -> TEMPO: %lld nanosegundos\n", j, (long long)elapsed);
                    
                    // -----> ESCREVER ARQUIVO
                    snprintf(path, sizeof(path), "temp/parcial_%d.txt", j);

                    FILE *file = fopen(path, "w");

                    if (file == NULL) exit(-1); 

                    fprintf(file, "%lld\n", (long long)elapsed);

                    fclose(file);

                    exit(0);               
                }

                blockStart = blockEnd + 1;
                blockEnd = blockEnd + blockSize;
                if (blockEnd > b) blockEnd = b;
            }

            for(int k = 0; k < w; k++) {
                // PROCESSO PAI AGUARDANDO FILHOS
                wait(NULL);
                printf("PROCESSO FILHO ACABOU (%d/%d)\n", k+1, w);
            }

        } else {
            // CICLICO
        }
    } 
    
    if (strcmp(argv[4], "thread") == 0) {
            // THREADS
    }
    
    
    
    
    // BLOCOS OU CICLICA
    
    

    // logica p/ PROCESSO + BLOCOS
    

    

    





    return 0;
}