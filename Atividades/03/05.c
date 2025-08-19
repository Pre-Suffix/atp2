// Exercicio 5 • Busca em Arquivo: Escreva um programa que procure por uma palavra específica em
// um arquivo de texto e exiba as linhas que contêm essa palavra.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Sintaxe incorreta. Sintaxe correta: %s <arquivo> <palavra>.", argv[0]);
        return 1;
    }

    FILE *arq = fopen(argv[1], "rb");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    int wordLen = strlen(argv[2]);

    int lineCount = 1;
    int startP = 0;
    int c = 0;
    for(int i = 0; c = fgetc(arq); i++) {
        if(c != '\n' && c != EOF) continue;

        fseek(arq, startP, SEEK_SET);
        int lineLen = i - startP;
        char *line = calloc(sizeof(char), lineLen + 2);
        fgets(line, lineLen + 2, arq);

        startP = i + 1;

        for(int j = 0; j < (lineLen - wordLen); ++j) {
            char *word = calloc(sizeof(char), wordLen + 2);
            strncpy(word, &line[j], wordLen);

            if(strcmp(word, argv[2]) == 0) {
                printf("Linha %d: %s", lineCount, line);
                free(word);
                break;
            }
            
            if(word != NULL) free(word);
        }

        free(line);
        lineCount++;

        if(c == EOF) break;
    }

    fclose(arq);
    return 0;
}