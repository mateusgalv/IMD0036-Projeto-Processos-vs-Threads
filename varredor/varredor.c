#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    int A, B;
    
    A = atoi(argv[1]);
    B = atoi(argv[2]);

    printf(" -> Intervalo [%d,%d]\n", A, B);
    
    for(int i = A; i <= B; i++) {
        contarPassos(i);   
    }
    return 0;
}

// gcc varredor.c -o varredor && ./varredor 10 12