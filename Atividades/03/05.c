// Exercicio 5 • Busca em Arquivo: Escreva um programa que procure por uma palavra específica em
// um arquivo de texto e exiba as linhas que contêm essa palavra.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct strbase {
    char *str;
    int len;
} String;

void addc(String *string, char c) {
    string->len++;
    string->str = realloc(string->str, sizeof(char) * (string->len + 1));
    if(string->str == NULL) exit(1);

    string->str[string->len - 1] = c;
    string->str[string->len] = '\0';
}

void clear(String *string) {
    if(string->str != NULL) free(string->str);

    string->len = 0;
    string->str = calloc(1, sizeof(char));
    if(string->str == NULL) exit(1);
}

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Sintaxe incorreta. Sintaxe correta: %s <arquivo> <palavra>.\n", argv[0]);
        return 1;
    }

    FILE *arq = fopen(argv[1], "rb");
    if(arq == NULL) {
        puts("Erro ao abrir o arquivo.");
        return 1;
    }

    int wordlen = strlen(argv[2]);

    String *line = malloc(sizeof(String));
    if(line == NULL) exit(1);

    clear(line);

    int c = 0;
    int linesFound = 0;

    for(int l = 0; 1;) {
        c = fgetc(arq);
        if(c != '\n' && c != EOF) {
            addc(line, c);
            continue;
        }

        l++;
        if(line->len < wordlen) {
            clear(line);

            if(c == EOF) break;
            continue;
        }

        for(int i = 0; i <= (line->len - wordlen); i++) {
            if(strncmp(&line->str[i], argv[2], wordlen) != 0) continue;

            printf("%d - %s\n", l, line->str);
            linesFound++;
            break;
        }

        clear(line);
        if(c == EOF) break;
    }

    if(linesFound == 0) puts("Nenhuma linha foi encontrada.");

    fclose(arq);
    return 0;
}