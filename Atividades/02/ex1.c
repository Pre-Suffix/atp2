// Exercicio 1 • Escreva um programa que leia uma string do usuário e imprima seu comprimento.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char string[101] = {'\0'};
    
    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    printf("Sua string tem comprimento %d.", strlen(string));

    return 0;
}