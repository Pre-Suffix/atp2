// Exercicio 4 • Implemente um programa que verifique se uma string é um palíndromo (lê-se igual de
// trás para frente, ignorando espaços e pontuação).
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char string[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    char stringLimpada[101] = {'\0'};
    int j = 0;
    for(int i = 0; i < strlen(string); i++) {
        if(
            (string[i] > 96 && string[i] < 123) ||
            (string[i] > 64 && string[i] < 91)
        ) {
            stringLimpada[j] = tolower(string[i]);
            j++;
        }
    }

    int len = strlen(stringLimpada);
    int palindromo = 1;
    for(int i = 0; i < len / 2; i++) {
        if(stringLimpada[i] != stringLimpada[len - i - 1]) {
            palindromo = 0;
            break;
        }
    }

    if(palindromo == 1) printf("Sua string e um palindromo.");
    else printf("Sua string nao e um palindromo.");

    return 0;
}