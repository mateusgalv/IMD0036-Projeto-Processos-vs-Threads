#include <string.h>
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
        printf(" --> Solução por Processos + Blocos - Tamanho dos blocos = %lld", blockSize);

        blockStart = input->a;
        blockEnd = (input->a + blockSize - 1);

        for(int i = 0; i < input->w; i++) {
            createProcess(i, blockStart, blockEnd);

            blockStart = blockEnd + 1;
            blockEnd = blockEnd + blockSize;
            if (blockEnd > input->b) blockEnd = input->b;
        }        
    } else if (strcmp(input->particao, "ciclico") == 0) {
        
    }


    return;
}