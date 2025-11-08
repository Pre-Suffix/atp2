// Atividade 10 - Exercicio 3 • Implementar em C os métodos de busca
// sequencial, sequencial ordenada e busca binária. Testar com
// diferentes conjuntos de dados.
#include <stdlib.h>
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

int buscaSequencial(int *vetor, int tamanho, int valor) {
    for(int i = 0; i < tamanho; i++) {
        if(vetor[i] != valor) continue;
        return i;
    }

    return -1;
}

int buscaSequencialOrdenada(int *vetor, int tamanho, int valor) {
    for(int i = 0; i < tamanho; i++) {
        if(vetor[i] != valor) continue;
    
        int tmp;
        for(; i > 0; i--) {
            tmp = vetor[i - 1];
            vetor[i - 1] = vetor[i];
            vetor[i] = tmp;
        }
        return 0;
    }

    return -1;
}

int buscaBinaria(int *vetor, int tamanho, int valor) {
    int e = 0, d = tamanho - 1, p = tamanho / 2;

    while(e <= d) {
        p = (e + d) / 2;

        if(vetor[p] == valor) d = e - 1;
        else if(vetor[p] < valor) e = p + 1;
        else d = p - 1;
    }

    if(vetor[p] == valor) return p;
    
    return -1;
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

    int valor = -1;
    while(escolha != 's' && escolha != 'o' && escolha != 'b') {
        printf("Digite o metodo de busca e o valor buscado (s = sequencial, o = ordenada, b = binaria): ");
        scanf(" %c %d", &escolha, &valor);

        if(escolha <= 'Z') escolha += 32;
    }

    int indx;
    if(escolha == 's')
        indx = buscaSequencial(vetor, vecsize, valor);
    else if(escolha == 'o')
        indx = buscaSequencialOrdenada(vetor, vecsize, valor);
    else {
        mergeSort(vetor, 0, vecsize - 1);
        indx = buscaBinaria(vetor, vecsize, valor);
    }

    vecprint(vetor, vecsize);

    if(indx == -1)
        printf("Valor nao encontrado.\n");
    else
        printf("Valor encontrado!\nvetor[%d] = %d\n", indx, vetor[indx]);

    return 0;
}