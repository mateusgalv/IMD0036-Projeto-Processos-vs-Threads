#include <stdio.h>

void readTempFiles(int w, long long *times) {
    for (int i = 0; i < w; i++) {
        char path[32];
        snprintf(path, sizeof(path), "temp/parcial_%d.txt", i);

        FILE *file = fopen(path, "r");
        if (file == NULL) return;

        int n = fscanf(file, "%lld", &times[i]);
        if (n != 1) printf("Ler arquivo %d falhou", i);

        fclose(file);
    }
}