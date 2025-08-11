// Exercicio 5 • Crie uma função que receba duas strings e retorne a maior substring em comum entre elas.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    char string[101] = {'\0'};
    char string2[101] = {'\0'};

    printf("Insira uma string: ");
    fgets(string, 100, stdin);

    printf("Insira outra string: ");
    fgets(string2, 100, stdin);

    int len = strlen(string);
    int len2 = strlen(string2);

    int subPtr = 0;
    int subLen = 0;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len2; j++) {
            int _subLen = 0;
            for(int k = 0; k < (len - i) && k < (len2 - j); k++) {
                if(string[i + k] != string2[j + k]) break;

                _subLen++;
                if(_subLen > subLen) {
                    subPtr = i;
                    subLen = _subLen;
                }
            }
        }
    }

    for(int i = 0; i < subLen; i++) putc(string[i + subPtr], stdout);

    return 0;
}