// Exercicio 6 • Concatenação de Arquivos: Desenvolva um programa que concatene o conteúdo de
// dois arquivos em um terceiro arquivo.
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 4) {
        printf("Sintaxe incorreta. Sintaxe correta: %s <arquivo 1> <arquivo 2> <destino>.\n", argv[0]);
        return 1;
    }

    FILE *arq1 = fopen(argv[1], "rb");
    FILE *arq2 = fopen(argv[2], "rb");
    if(arq1 == NULL || arq2 == NULL) {
        puts("Erro ao abrir um dos arquivos fonte.");
        return 1;
    }

    FILE *dest = fopen(argv[3], "wb");
    if(dest == NULL) {
        puts("Erro ao abrir o arquivo destino.");
        return 1;
    }

    int c = 0;
    while((c = fgetc(arq1)) != EOF) fputc(c, dest);
    fclose(arq1);

    puts("Primeiro arquivo copiado.");

    c = 0;
    while((c = fgetc(arq2)) != EOF) fputc(c, dest);
    fclose(arq2);

    puts("Cópia finalizada.");
    fclose(dest);
    return 0;
}