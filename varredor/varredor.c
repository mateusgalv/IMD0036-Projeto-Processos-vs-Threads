#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int MATRICULA = 007273;

bool isEven(int number) {
    if (number%2 == 0) {
        return true;
    } else {
        return false;
    }
}

int contarPassos(int number) {
    int cont = 0;

    printf("Numero = %d - ", number);

    while (number != 1) {

        if (isEven(number)) {
            number = number/2;
        } else {
            number = (number*3)+1;
        }

        cont ++;
    }

    printf("Passos = %d\n", cont);

    return 0;
}

// ./varredor <A> <B> <W> <modo> <particao> <arquivo_saida>
int main(int argc, char *argv[]) {
    int A, B, W;
    
    A = atoi(argv[1]);
    B = atoi(argv[2]);
    W = atoi(argv[3]);

    if (A <= 0 || B <= 0 || B < A) {
        // validação argumentos <A> <B>
        printf("O intervalo [%d, %d] é inválido\n", A, B);
        return 0;
    } else if (W < 1) {
        // validação argumento <W>
        printf("Numero de threads/processos %d é inválido\n", W);
        return 0;
    }
    
    // A = A + MATRICULA;
    printf(" -> Intervalo [%d,%d]\n", A, B);
    
    if (W == 1) {
        // Sequencial
        printf(" -> W = 1 - Execução sequencial\n");
        
        for(int i = A; i <= B; i++) {
            contarPassos(i);   
        }
        
    } else {
        // bloco ou ciclico
        printf(" -> W = %d - Execução não sequencial\n", W);
    }

    return 0;
}

// gcc varredor.c -o varredor && ./varredor 10 12 1