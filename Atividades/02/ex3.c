// Exercicio 3 • Escreva uma função que conte o número de vogais em uma string.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int vogal(char c) {
    char *vogais = "aeiouAEIOU";

    for(int i = 0; i < strlen(vogais); i++) if(c == vogais[i]) return 1;

    return 0;
}

int main(void) {
    char string[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    int len = strlen(string);
    int cVogais = 0;
    for(int i = 0; i < len; ++i) if(vogal(string[i]) == 1) cVogais++;

    printf("Sua string tem %d vogais.", cVogais);

    return 0;
}