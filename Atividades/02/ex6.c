// Exercicio 6 • Escreva um programa que remova todos os espaços em branco de uma string.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void removerBrancos(char *str) {
    int size = strlen(str);
    char *finalString = calloc(size, sizeof(char));

    int j = 0;
    for(int i = 0; i < size; i++) {
        if(str[i] == ' ') continue;

        finalString[j] = str[i];
        j++;
    }

    strcpy(str, finalString);
}

int main(void) {
    char string[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    removerBrancos(string);

    puts(string);

    return 0;
}