// Exercicio 3 • Contagem de Linhas: Desenvolva um programa que conte o número de linhas em um
// arquivo de texto e exiba o resultado.
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Sintaxe incorreta. Sintaxe correta: %s <caminho para o arquivo>.", argv[0]);
        return 1;
    }

    FILE *arq = fopen(argv[1], "r");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo, verifique o caminho do arquivo.");
        return 1;
    }

    int linhas = 1;
    while(!feof(arq)) {
        if(fgetc(arq) == '\n') linhas++;
    }

    printf("O arquivo tem %d linhas.", linhas);

    fclose(arq);

    return 0;
}