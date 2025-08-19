// Exercicio 4 • Cópia de Arquivo: Crie um programa que copie o conteúdo de um arquivo para outro. O
// usuário deve fornecer os nomes dos arquivos de origem e destino.
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 3) {
        printf("Sintaxe incorreta. Sintaxe correta: %s <fonte> <destino>.", argv[0]);
        return 1;
    }

    FILE *source = fopen(argv[1], "rb");
    if(source == NULL) {
        printf("Erro ao abrir o arquivo de origem.");
        return 1;
    }

    FILE *destination = fopen(argv[2], "wb");
    if(destination == NULL) {
        printf("Erro ao abrir o arquivo de desitno.");
        fclose(source);
        return 1;
    }

    int c = 0;
    while(1) {
        c = fgetc(source);
        if(c == EOF) break;

        fputc(c, destination);
    }

    fclose(source);
    fclose(destination);

    return 0;
}