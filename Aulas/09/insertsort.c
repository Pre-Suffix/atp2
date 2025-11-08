#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void insertSort(int x[], int n) {
    int i, k, y;
    for(k = 1; k < n; k++) {
        y = x[k];
        for(i = k - 1; i >= 0 && y < x[i]; i -= 1)
            x[i + 1] = x[i];

        x[i + 1] = y;
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
    insertSort(vec, tamanho_vetor);
    vecprint(vec, tamanho_vetor);
    
    return 0;
}