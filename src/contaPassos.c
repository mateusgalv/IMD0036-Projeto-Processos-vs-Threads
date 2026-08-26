#include <stdio.h>
#include <stdint.h>

#include "isEven.h"

int64_t contaPassos(int64_t number) {
    int64_t cont = 0;

    printf("Numero = %lld - ", (long long)number);

    while (number != 1) {

        if (isEven(number)) {
            number = (number / 2);
        } else {
            number = (number * 3) + 1;
        }

        cont++;
    }
    
    printf("Passos = %lld\n", (long long)cont);
    return cont;
}