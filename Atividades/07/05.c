// Exercicio 5 • Modifique o programa anterior para calcular
// o MDC de três ou mais números.
#include <stdlib.h>
#include <stdio.h>

// Utiliza o algorítmo de Euclides em forma recursiva para
// obter o MDC de dois valores positivos. Explicação de
// como funciona localizada em "./04.c".
unsigned int mdc_duplo(unsigned int a, unsigned int b) {
    if(a < b) {
        int t = b;
        b = a;
        a = t;
    }

    if(b == 0) return a;

    return mdc_duplo(b, a % b);
}

// Utilizando-se da propriedade associativa do MDC
// (MDC(a,b,c) = MDC(a, MDC(b, c))), recursivamente vamos
// modificando o penúltimo valor de um vetor para ser o MDC
// dos dois últimos valores do vetor, até obter um único valor. 
unsigned int mdc_multiplo(unsigned int *nums, size_t tamanho) {
    if(tamanho < 2) return 0;
    else if(tamanho == 2) return mdc_duplo(nums[0], nums[1]);

    nums[tamanho - 2] = mdc_duplo(nums[tamanho - 1], nums[tamanho - 2]);

    return mdc_multiplo(nums, tamanho - 1);
}

int main(void) {
    size_t vetor_tamanho = 0;
    printf("Insira quantos valores vai calcular: ");
    scanf("%llu", &vetor_tamanho);

    if(vetor_tamanho == 0) return -1;

    unsigned int *nums = (unsigned int *) malloc(sizeof(unsigned int) * vetor_tamanho);
    printf("Insira os valores: ");
    for(size_t i = 0; i < vetor_tamanho; i++)
        scanf("%u", &nums[i]);

    printf("MDC = %u", mdc_multiplo(nums, vetor_tamanho));

    return 0;
}