#include <stdio.h>
#include <stdbool.h>

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
            // isOdd
            number = (number*3)+1;
        }
        cont ++;
        // printf("Passo %d: %d\n",cont,number);
    }

    printf("Contador = %d\n", cont);

    return 0;
}

int main() {
    int number, A, B;
    
    A = 10;
    B = 12;
    
    for(int i = A; i <= B; i++) {
        contarPassos(i);   
    }
    return 0;
}