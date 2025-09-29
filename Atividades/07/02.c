// Exercicio 2 • Inversão de String: Uma função recursiva
// para inverter uma string. A função deve modificar a string
// original e não criar uma nova string. Considere que a
// função recebe como parâmetros a string, o índice de início
// e o índice de fim (ou seja, a posição no array do primeiro
// e do último caracter da string). Faça com que a função
// main escreva a string antes e depois da chamada da função
// recursiva.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Inverte os caracteres de uma dada string.
//
// Como funciona:
//   1. Inverte os caracteres colocados nas posições dadas
//      como iniciais e finais.
//
//   2. Se a distância entre os caracteres colocados nas
//      posições iniciais e finais for menor ou igual a 1,
//      retorne, visto que nesse momento todos os caracteres
//      foram invertidos.
//
//   3. Caso a distância não seja menor ou igual a 1, chame
//      a função de novo, só que com valores de inicio e fim
//      2 casas mais próximas. Dessa forma, vamos de par em
//      par invertendo os caracteres até não ter mais o que
//      inverter.
void inverter_string(char *string, int inicio, int fim) {
    char temp = string[inicio];
    string[inicio] = string[fim];
    string[fim] = temp;

    if(abs(inicio - fim) <= 1) return;

    inverter_string(string, inicio + 1, fim - 1);
}

int main(void) {
    char *string = (char *) calloc(100, sizeof(char));
    printf("Insira uma string: ");

    fflush(stdin);
    fgets(string, 100, stdin);

    size_t len = strlen(string);
    
    // Devido a forma em que fgets(3) funciona, o último valor
    // vai ser o caractere '\n', que é indesejado.
    string[len - 1] = '\0';

    printf("%s\n", string);

    inverter_string(string, 0, len - 2);

    printf("%s\n", string);

    return 0;
}