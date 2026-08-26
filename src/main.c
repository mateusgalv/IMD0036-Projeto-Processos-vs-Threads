#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "isEven.h"
#include "contaPassos.h"
#include "ceilDivision.h"

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

    // INICIO VALIDAÇÃO
    if (a <= 0 || b <= 0 || b < a) {
        // validação argumentos <A> e <B>
        printf("O intervalo [%lld, %lld] é inválido\n", (long long)a, (long long)b);
        return 0;
    } else if (w < 1 || w > 8) {
        // validação argumento <W>
        printf("Número de processos inválido, -> uso intervalo [1,8]\n");
        return 0;
    } else if (strcmp(argv[4], "processo") != 0) {
        // validação argumento <modo>
        printf("Modo de processamento inválido\n");
        return 0;
    }
    // FIM VALIDAÇÃO

    printf(" -> Intervalo [%lld,%lld]\n", (long long)a, (long long)b);

    if (w == 1) {
        // Contagem sequencial
        printf(" -> W = 1 - Execução sequencial\n");
        
        for(int64_t i = a; i <= b; i++) {
            contaPassos(i);
        }

        return 0;
    } 

    printf(" -> W = %d - Execução não sequencial\n", w);
    length = b - a + 1;
    printf(" -> Comprimento = %lld\n", (long long)length);

    blockSize = ceilDivision(length, w);
    printf(" -> Tamanho arredondado dos blocos = %lld\n", (long long)blockSize);
 
    return 0;
}