// NOTA: Desenvolvido usando as especificações de C23, isso é,
// com a inclusão de nullptr e nullptr_t.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Exercício 4 • Considere a seguinte versão simplificada de
// uma ficha para cadastro de funcionário de uma empresa:
//
//            [  NUMERO_MATRICULA  |  NOME  ]
//
// Assumindo que o sistema utiliza uma lista encadeada
// dinâmica para armazenar as informações dos funcionários, e
// que os números das matrículas estão no intervalo 1-10:

//    a) Definir o registro regFunc, para cadastro de
// funcionários, e declarar a variável global "tipo ponteiro"
// listaRFunc
struct regFunc_t {
    unsigned int numMatricula;
    char nome[100];
    struct regFunc_t *prox;
};

typedef struct regFunc_t regFunc;

regFunc *listaRFunc = nullptr;

int main(void) {
    listaRFunc = calloc(1, sizeof(regFunc));
    if(listaRFunc == nullptr) {
        puts("Erro na alocação.");
        return 1;
    }

//    b) Construir um subprograma para realizar a leitura dos
//  dados (matrícula e nome), a partir do teclado, de um
//  funcionário a ser cadastrado, e incluir este novo registro
//  de funcionário na lista de funcionários.

    regFunc *no = listaRFunc;
    int continuar = 1;
    int n = 0;
    while(1) {
        if(n >= 10) break;

        printf("Parar inserção de novos funcionários? (1=sim, 0=não): ");
        fflush(stdin);
        scanf("%d", &continuar);

        if(continuar == 1) break;

        no->prox = calloc(1, sizeof(regFunc));
        if(no->prox == nullptr) {
            puts("Erro na alocação.");
            return 1;
        }

        printf("Número de Matrícula: ");
        fflush(stdin);
        scanf("%u", &no->numMatricula);

        printf("Nome: ");
        fflush(stdin);
        fgets(no->nome, 100, stdin);
        no->nome[strcspn(no->nome, "\n")] = 0;

        printf("Funcionário inserido no registro.\n");

        no = no->prox;
        n++;
    }

//    c) Fazer um subprograma que percorra a lista montada
//  escrevendo Número de Matrícula e Nome de cada nó.
    printf("Funcionários no registro:\n\n");

    no = listaRFunc;
    for(int i = 1; no->prox != nullptr; i++) {
        printf("%d - %s (%u)\n", i, no->nome, no->numMatricula);
        no = no->prox;
    }

    return 0;
}