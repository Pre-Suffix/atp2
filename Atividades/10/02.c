// Atividade 10 - Exercicio 2 • Implementar em C os métodos SelectSort e
// Two-way MergeSort, e testá-los com diferentes conjuntos de entrada.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define VECPRINT_LIM 20

void vecprint(int *vetor, int l) {
    printf("[ ");
    for(int i = 0; i < l; i++) {
        printf("%d ", vetor[i]);

        if(i == VECPRINT_LIM / 2) {
            i = l - (VECPRINT_LIM / 2);
            printf("... ");
        }
    }
    printf("]\n");
}

void selectSort(int *vetor, int ini, int fim) {
    int maior, maiori;
    for(int l = fim; l >= (ini + 1); l--) {
        maior = -INT_MAX;
        maiori = -1;

        for(int i = 0; i <= l; i++) {
            if(vetor[i] > maior) {
                maior = vetor[i];
                maiori = i;
            }
        }

        vetor[maiori] = vetor[l];
        vetor[l] = maior;
    }
}

void merge(int *vetor, int ini, int pivo, int fim) {
    int *_vec = (int *) calloc(fim - ini + 1, sizeof(int));
    int ie = ini, c = 0, id = pivo + 1;

    for(; ie <= pivo && id <= fim; c++) {
        if(vetor[ie] < vetor[id])
            _vec[c] = vetor[ie++];
        else
            _vec[c] = vetor[id++];
    }

    while(ie <= pivo) _vec[c++] = vetor[ie++];
    while(id <= fim ) _vec[c++] = vetor[id++]; 

    for(int i = ini; i <= fim; i++)
        vetor[i] = _vec[i - ini];
    
    free(_vec);    
}

void mergeSort(int *vetor, int ini, int fim) {
    int pivo = -1;

    if(ini < fim) {
        pivo = (ini + fim) / 2;
        mergeSort(vetor, ini, pivo);
        mergeSort(vetor, pivo + 1, fim);

        merge(vetor, ini, pivo, fim);
    }
}

int main(void) {
    int *vetor = NULL, vecsize = 0;

    while(vecsize <= 0) {
        printf("Defina tamanho do vetor: ");
        scanf(" %d", &vecsize);
    }

    vetor = (int *) malloc(sizeof(int) * vecsize);
    if(vetor == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(-1);
    }

    char escolha = '\0';
    while(escolha != 'm' && escolha != 'a') {
        printf("Como preencher o vetor? (m = manual, a = aleatorio): ");
        scanf(" %c", &escolha);

        if(escolha <= 'Z') escolha += 32;
    }

    if(escolha == 'm') {
        printf("Digite os valores do vetor separados por espaço:\n");
        for(int i = 0; i < vecsize; i++) scanf("%d", &vetor[i]);
    } else {
        srand(time(NULL));
        for(int i = 0; i < vecsize; i++) vetor[i] = rand();
    }


    clock_t inicio, fim;
    // SELECT SORT
    int *vetor_select = (int *) malloc(sizeof(int) * vecsize);
    memcpy(vetor_select, vetor, vecsize * sizeof(int));
    printf("Select sort:\n");

    vecprint(vetor_select, vecsize);

    inicio = clock();
    selectSort(vetor_select, 0, vecsize - 1);
    fim = clock();

    vecprint(vetor_select, vecsize);

    printf("Tempo: %.3fs\n\n", (float) (fim - inicio) / CLOCKS_PER_SEC);
    free(vetor_select);

    // MERGE SORT
    printf("Merge sort:\n");

    vecprint(vetor, vecsize);

    inicio = clock();
    mergeSort(vetor, 0, vecsize - 1);
    fim = clock();

    vecprint(vetor, vecsize);

    printf("Tempo: %.3fs\n\n", (float) (fim - inicio) / CLOCKS_PER_SEC);

    return 0;
}