// Exercicio 9 • Complementar o programa da aula passada de
// modo a incluir os métodos InsertSort, ShellSort e 
// SelectSort, dependendo da escolha do usuário. Testá-los com
// diferentes conjuntos de dados de entrada, comparando os dois
// métodos.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

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

void insertsort(int *vec, int n) {
    int i, k, y;
    for(k = 1; k < n; k++) {
        y = vec[k];
        for(i = k - 1; i >= 0 && y < vec[i]; i -= 1)
            vec[i + 1] = vec[i];

        vec[i + 1] = y;
    }
}

void shellsort(int *vec, int n) {
    for(int dist = log2(n) - 1; dist > 0; dist /= 2) {
        int i, k, y;

        for(k = dist; k < n; k++) {
            y = vec[k];

            for(i = k; i >= dist && y < vec[i - dist]; i -= dist)
                vec[i] = vec[i - dist];
            
            vec[i] = y;
        }
    }
}

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
    while(escolha != 'b' && escolha != 'q' && escolha != 'i' && escolha != 's' && escolha != 'l') {
        printf("Escolha o algoritimo (b = Bubble Sort, q = QuickSort, i = Insertion Sort, s = Shell Sort, l = Select Sort): ");
        scanf(" %c", &escolha);
    }

    int TAMANHO_VETOR = 0;
    while(TAMANHO_VETOR <= 0) {
        printf("Defina o tamanho do vetor: ");
        scanf(" %d", &TAMANHO_VETOR);
    }

    int *vetor = malloc(sizeof(int) * TAMANHO_VETOR);
    for(int i = 0; i < TAMANHO_VETOR; i++)
        vetor[i] = rand();

    printf("Vetor original: (%d itens)\n", TAMANHO_VETOR);
    vecprint(vetor, TAMANHO_VETOR);

    clock_t comeco = clock();

    if(escolha == 'b')
        bubblesort(vetor, TAMANHO_VETOR);
    else if(escolha = 'q')
        quicksort(vetor, 0, TAMANHO_VETOR - 1);
    else if(escolha == 'i')
        insertsort(vetor, TAMANHO_VETOR);
    else if(escolha == 'l')
        selectsort(vetor, TAMANHO_VETOR);
    else
        shellsort(vetor, TAMANHO_VETOR);

    clock_t final = clock();

    printf("Vetor final:\n");
    vecprint(vetor, TAMANHO_VETOR);

    printf("Tempo gasto: %lfs\n", (double)(final - comeco) / CLOCKS_PER_SEC);

    return 0;
}