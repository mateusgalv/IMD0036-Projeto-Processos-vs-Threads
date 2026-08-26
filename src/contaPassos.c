#include "isEven.h"

int contaPassos(int number) {
    int cont = 0;

    printf("Numero = %d - ", number);

    while (number != 1) {

        if (isEven(number)) {
            number = number/2;
        } else {
            number = (number*3)+1;
        }

        cont++;
    }
    
    printf("Passos = %d\n", cont);
    return cont;
}