// Exercicio 6 • Calcular o valor de um termo da sequência de
// Fibonacci, sendo o primeiro termo o de número zero.
// O termo deve ser lido e passado como parâmetro para a função.
#include <stdlib.h>
#include <stdio.h>

int fib(int n) {
    if(n <= 1) return n;

    return fib(n - 1) + fib(n - 2);
}

int main(void) {
    int n = 0;
    printf("Insira um número: ");
    scanf("%d", &n);

    printf("F%d: %d\n", n, fib(n));

    return 0;
}