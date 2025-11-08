#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void swap(int *v1, int *v2) {
    int tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
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

void printvec(int *vec, int _tam) {
    printf("[ ");
    for(int i = 0; i < _tam; i++)
        printf("%d ", vec[i]);
    
    printf("]\n");
}

int main(void) {
    srand(time(NULL));
    int vecsize = 100;
    scanf("%d", &vecsize);

    if(vecsize < 1) return -1;

    int *vec = malloc(vecsize * sizeof(int));
    for(int i = 0; i < vecsize; i++)
        vec[i] = rand(), vec[i] = (vec[i] == 0 ? 1 : vec[i]);

    printvec(vec, vecsize);

    quicksort(vec, 0, vecsize - 1);

    printvec(vec, vecsize);

    return 0;
}