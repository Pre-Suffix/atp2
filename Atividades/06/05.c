// Exercicio 5 • Verificar se um número inteiro é primo ou não.
#include <stdlib.h>
#include <stdio.h>

int primo(int num, int div) {
    if(div <= 1) return 1;
    else if (num % div == 0) return 0;

    return primo(num, div - 1);
}

int main(void) {
    int n = 0;
    printf("Insira um numero: ");
    scanf("%d", &n);

    if(primo(n, n-1))
        printf("O valor é primo!");
    else
        printf("O valor não é primo.");

    return 0;
}