// Exercicio 1 • Ler um número inteiro maior que 9 e
// escreve-lo dígito a dígito, ou seja, se n = 296, será
// escrito 2, 9, 6. Utilize o operador mod (%) na solução.
#include <stdlib.h>
#include <stdio.h>

void escreverNumero(int n) {
    if(n <= 0) return;

    escreverNumero(n / 10);

    putchar(48 + (n % 10));
    putchar(' ');
}

int main(void) {

    int n = 0;
    scanf("%d", &n);

    escreverNumero(n);

    return 0;
}