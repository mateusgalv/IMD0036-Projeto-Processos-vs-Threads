#include <string.h>
#include <stdio.h>
#include "InputData.h"
#include "OutputData.h"
#include "createProcess.h"
#include "ceilDivision.h"

void solveProcess(
    InputData *input,
    OutputData *output
){
    if (strcmp(input->particao, "bloco") == 0) {
        long long blockSize, blockStart, blockEnd;
        output->length = (input->b - input->a - 1);
        blockSize = ceilDivision(output->length, input->w);
        blockStart = input->a;
        blockEnd = (input->a + blockSize - 1);

        printf(" --> Solução por Processos + Blocos - Tamanho dos blocos = %lld\n", blockSize);

        for(int i = 0; i < input->w; i++) {
            createProcess(i, blockStart, blockEnd, 1);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > input->b) blockEnd = input->b;
        }        
    } else if (strcmp(input->particao, "ciclico") == 0) {
        printf(" --> Solução por Processos + Ciclico, Incremento = %d\n", input->w);

        for (int i = 0; i < input->w; i++) {
            createProcess(i, input->a, input->b, input->w);
        }
    }


    return;
}