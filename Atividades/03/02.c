// Exercicio 2 • Leitura e Exibição: Escreva um programa que leia o conteúdo do arquivo "nomes.txt"
// criado no exercício anterior e exiba os nomes na tela
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *nomes = fopen("./nomes.txt", "r");

    if(nomes == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for(int i = 0; (i < 5) && !feof(nomes); i++) {
        char nome[151] = {'\0'};
        fgets(nome, 150, nomes);
        fputs(nome, stdout);
    }

    fclose(nomes);

    return 0;
}