// Exercicio 4 • Elevar um número inteiro a qualquer
// potência, sem usar comandos específicos da linguagem C.
// Devem ser fornecidos o número e a potência.
#include <stdlib.h>
#include <stdio.h>

long long int potencia(long long int base, long long int expoente) {
    if(expoente <= 1) return base;

    return base * potencia(base, expoente - 1);
}

int main(void) {
    long long int base = 0;
    long long int expoente = 0;

    printf("Insira a base: ");
    scanf("%lld", &base);

    printf("Insira o expoente: ");
    scanf("%lld", &expoente);

    printf("%lld^%lld = %lld\n", base, expoente, potencia(base, expoente));

    return 0;
}