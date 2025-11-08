// Exercicio 7 • Implemente uma função que converta uma string para maiúsculas sem usar a função
// toupper().
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char toUpper(char c) {
    return c - (c > 96 && c < 123 ? 32 : 0);
}

int main(void) {
    char string[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    for(int i = 0; i < strlen(string); i++) putc(toUpper(string[i]), stdout);

    return 0;
}