#include <stdio.h>
#include <stdint.h>

#include "isEven.h"

int64_t stepsCount(int64_t number) {
    int64_t count = 0;

    // printf("Numero = %lld - ", (long long)number);

    while (number != 1) {

        if (isEven(number)) {
            number = (number / 2);
        } else {
            number = (number * 3) + 1;
        }

        count++;
    }
    
    // printf("Passos = %lld\n", (long long)count);
    return count;
}