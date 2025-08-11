// Exercicio 2 • Crie um programa que leia uma string e a imprima de trás para frente.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char string[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    strcpy(string, strrev(string));
    puts(string);

    return 0;
}