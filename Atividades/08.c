// Exercicio 8 • Fazer um programa em C que ordena um
// conjunto de números inteiros utilizando os métodos
// BubbleSort ou QuickSort, dependendo da escolha do usuário.
// Testá-los com diferentes conjuntos de dados de entrada,
// comparando os dois métodos.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define TAMANHO_VETOR 50000

void trocar(int *v1, int *v2) {
    int tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

void bubblesort(int *vec, int size) {
    for(int i = 0; i < size - 1; i++) {
        int troca = 0;
        for(int j = 0; j < size - i - 1; j++) {
            if(vec[j] > vec[j + 1]) {
                trocar(&vec[j], &vec[j + 1]);
                troca = 1;
            }
        }

        if(troca == 0) return;
    }
}

int particao(int *vec, int min, int max, int pivo_i) {
    int pivo = vec[pivo_i];

    int *_vec = malloc(sizeof(int) * (max - min + 1));
    if(_vec == NULL) return -1;

    int is = 0, ie = max - min;
    for(int i = min; i <= max; i++) {
        if(i == pivo_i) continue;

        if(vec[i] < pivo) {
            _vec[is] = vec[i];
            is++;
        } else {
            _vec[ie] = vec[i];
            ie--;
        }
    }

    _vec[is] = pivo;
    
    memcpy(vec + min, _vec, sizeof(int) * (max - min + 1));
    free(_vec);

    return is + min;
    
}

void quicksort(int *vec, int min, int max) {
    if(min >= max) return;

    int pivo_i = (max - min) / 2 + min;

    pivo_i = particao(vec, min, max, pivo_i);

    if(pivo_i == -1) return;

    if(pivo_i != 0) quicksort(vec, min, pivo_i - 1);
    quicksort(vec, pivo_i + 1, max);

}

void vecprint(int *vec, int size) {
    printf("[ ");

    for(int i = 0; i < size; i++) {
        printf("%d ", vec[i]);

        if(i == 9) {
            printf("... ");
            i = size - 10;
        }
    }

    printf("]\n");
}

int main(void) {
    srand(time(NULL));
    
    char escolha = '\0';
    while(escolha != 'b' && escolha != 'q') {
        printf("Escolha o algoritimo (b = Bubble Sort, q = QuickSort): ");
        scanf(" %c", &escolha);
    }

    int *vetor = malloc(sizeof(int) * TAMANHO_VETOR);
    for(int i = 0; i < TAMANHO_VETOR; i++)
        vetor[i] = rand();

    printf("Vetor original: (%d itens)\n", TAMANHO_VETOR);
    vecprint(vetor, TAMANHO_VETOR);

    clock_t comeco = clock();

    if(escolha == 'b')
        bubblesort(vetor, TAMANHO_VETOR);
    else
        quicksort(vetor, 0, TAMANHO_VETOR - 1);

    clock_t final = clock();

    printf("Vetor final:\n");
    vecprint(vetor, TAMANHO_VETOR);

    printf("Tempo gasto: %lfs\n", (double)(final - comeco) / CLOCKS_PER_SEC);

    return 0;
}