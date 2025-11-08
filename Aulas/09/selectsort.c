#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void selectsort(int *vec, int n) {
    int max_v, max_i;
    for(int i = n; i > 0; i--) {
        max_v = 0, max_i = 0;

        for(int j = 0; j < i; j++) {
            if(vec[j] > max_v) {
                max_v = vec[j];
                max_i = j;
            }
        }

        vec[max_i] = vec[i - 1];
        vec[i - 1] = max_v;
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
    selectsort(vec, tamanho_vetor);
    vecprint(vec, tamanho_vetor);
    
    return 0;
}