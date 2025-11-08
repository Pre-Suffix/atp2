// Exercicio 1 • Criação e Escrita Básica: Crie um programa que solicite ao usuário para inserir 5 nomes
// e os salve em um arquivo de texto chamado "nomes.txt", um nome por linha.
#include <stdio.h>

int main(void) {
    FILE *nomes = fopen("./nomes.txt", "w");

    if(nomes == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    for(int i = 1; i <= 5; i++) {
        fflush(stdin);

        char nome[101] = {'\0'};
        printf("Nome %d: ", i);
        fgets(nome, 100, stdin);

        fprintf(nomes, "%d - ", i);
        fputs(nome, nomes);
    }

    fclose(nomes);

    return 0;
}