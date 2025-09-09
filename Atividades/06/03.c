// Exercicio 3 • Calcular a soma dos n primeiros inteiros
// positivos, sendo n um valor lido e passado como parâmetro
// para a função.
#include <stdlib.h>
#include <stdio.h>

unsigned int somaPositiva(unsigned int num) {
    if(num == 0) return 0;

    return num + somaPositiva(num - 1);
}

int main(void) {
    unsigned int n = 0;
    printf("Insira um numero positivo: ");
    scanf("%u", &n);

    printf("Soma positiva até %d: %d", n, somaPositiva(n));

    return 0;
}