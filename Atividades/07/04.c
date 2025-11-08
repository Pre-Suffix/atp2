// Exercicio 4 • Cálculo do Máximo Divisor Comum (MDC)
// Contexto: o MDC de dois ou mais números inteiros é o maior
// número inteiro que divide todos eles sem deixar resto.
// Objetivo: Implementar uma função recursiva em C que
// calcule o MDC de dois números inteiros positivos
// utilizando o algoritmo de Euclides.
//
// O algoritmo de Euclides para encontrar o MDC de dois
// números a e b é baseado no princípio de que o MDC de dois
// números não muda se o número menor for subtraído do maior.
// Mais eficientemente, isso pode ser feito usando o operador
// de módulo (resto da divisão).
//
// Implemente uma função recursiva chamada mdc que aceite
// dois parâmetros inteiros positivos, a e b. A função deve
// retornar o MDC desses dois números usando o algoritmo de
// Euclides. Crie um programa principal que solicite ao
// usuário dois números inteiros positivos. Chame a função
// mdc com esses números e exiba o resultado.
#include <stdlib.h>
#include <stdio.h>

// Utiliza o algorítmo de Euclides em forma recursiva para
// obter o MDC de dois valores positivos.
//
// Como funciona:
//   1. A função primeiro verifica se b > a, se for ela os
//      inverte. Isso é necessário pois o algorítimo de
//      Euclides precisa saber qual é o maior valor entre
//      os dois.
//
//   2. Se o menor valor for igual a 0, então chegamos ao
//      MDC dos dois valores, que é igual ao maior valor.
//
//   3. Caso a condição anterior não seja verdadeira,
//      obtemos o módulo do maior valor com o menor valor,
//      pois o MDC do maior valor MOD menor valor e o menor
//      valor é igual ao MDC do maior valor com o menor valor.
unsigned int mdc(unsigned int a, unsigned int b) {
    // Garantir sempre que a > b.
    if(a < b) {
        int t = b;
        b = a;
        a = t;
    }

    if(b == 0) return a;

    return mdc(b, a % b);
}

int main(void) {
    unsigned int a = 0, b = 0;

    printf("Insira dois valores positivos: ");
    scanf("%u %u", &a, &b);

    printf("MDC(%u, %u) = %u\n", a, b, mdc(a, b));

    return 0;
}