#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void shellSort(int x[], int n) {
    for(int dist = log2(n) - 1; dist > 0; dist /= 2) {
        int i, k, y;

        for(k = dist; k < n; k++) {
            y = x[k];

            for(i = k; i >= dist && y < x[i - dist]; i -= dist)
                x[i] = x[i - dist];
            
            x[i] = y;
        }
    }
}

void vecprint(int *x, int n) {
    printf("[ ");
    for(int i = 0; i < n; i++) printf("%d ", x[i]);
    printf("]\n");
}

int main(void) {
    int tamanho_vetor = 0;
    printf("Tamanho do vetor: ");
    scanf(" %d", &tamanho_vetor);
    if(tamanho_vetor <= 0) return -1;

    int *vec = (int *) malloc(sizeof(int) * tamanho_vetor);
    srand(time(NULL));

    for(int i = 0; i < tamanho_vetor; i++) vec[i] = rand();

    vecprint(vec, tamanho_vetor);
    shellSort(vec, tamanho_vetor);
    vecprint(vec, tamanho_vetor);
    
    return 0;
}