// Exercicio 1 • Soma de Dígitos: Uma função recursiva que
// calcule a soma dos dígitos de um número inteiro positivo.
#include <stdlib.h>
#include <stdio.h>

// Performa a soma dos dígitos de um inteiro positivo.
//
// Como funciona:
//   1. Verifique se o número obtido é menor que 10,
//      se for, retorne-o. Isso por que a soma dos
//      digitos de qualquer número menor que 10 é
//      ele mesmo.
//
//   2. Retorne a soma do último digito (numero % 10)
//      com a soma dos outros digitos
//      (soma_digitos(numero / 10)). Devido a natureza
//      recursiva dessa função, em algum momento
//      chamaremos a função com um número < 10.
//
unsigned int soma_digitos(unsigned int numero) {
    if(numero < 10) return numero;

    return numero % 10 + soma_digitos(numero / 10);
}

// Função main para testar o algorítimo acima.
int main(void) {
    unsigned int numero = 0;
    printf("Insira um numero positivo: ");
    scanf("%u", &numero);

    printf("A soma dos digitos de %u = %u\n", numero, soma_digitos(numero));

    return 0;
}