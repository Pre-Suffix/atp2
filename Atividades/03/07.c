// Exercicio 7 • Registro de Alunos: Crie um programa que permita ao usuário cadastrar alunos (nome,
// idade e nota) em um arquivo binário. O programa deve ter opções para adicionar novos
// alunos, listar todos os alunos e buscar um aluno pelo nome.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[101];
    int idade;
    float nota;
} Aluno;

int main(void) {
    FILE *_alunos = fopen("alunos.data", "rb");
    Aluno *alunos = calloc(1, sizeof(Aluno));
    int cAlunos = 0;

    if(_alunos != NULL) {
        int filesize = 0;
        while(fgetc(_alunos) != EOF) filesize++;
        rewind(_alunos);
        cAlunos = filesize / sizeof(Aluno);

        free(alunos);
        alunos = calloc(cAlunos, sizeof(Aluno));

        fread(alunos, sizeof(Aluno), cAlunos, _alunos);
        fclose(_alunos);
    }

    while(1) {
        int opcao = 0;
        printf("\nTem %d aluno(s) no registro. O que pretende fazer?\n1 - Cadastrar novo aluno\n2 - Listar todos os alunos\n3 - Buscar pelo nome\n4 - Salvar e sair\n> ", cAlunos);

        fflush(stdin);
        scanf("%d", &opcao);

        if(opcao == 1) {
            alunos = (Aluno *) _recalloc(alunos, cAlunos + 1, sizeof(Aluno));

            fflush(stdin);
            printf("(Aluno %d)\nNome: ", cAlunos + 1);
            fgets(alunos[cAlunos].nome , 101, stdin);

            fflush(stdin);
            printf("Idade: ");
            scanf("%d", &alunos[cAlunos].idade);

            fflush(stdin);
            printf("Nota: ");
            scanf("%f", &alunos[cAlunos].nota);

            printf("Aluno adicionado ao registro.\n");

            cAlunos++;

            continue;
        }
        
        if(opcao == 2) {
            if(cAlunos == 0) {
                printf("Nao tem alunos no registro.\n");
                continue;
            }

            for(int i = 0; i < cAlunos; i++)
                printf("(Aluno %d)\n - Nome: %s - Idade: %d\n - Nota: %0.2f\n\n", i + 1, alunos[i].nome, alunos[i].idade, alunos[i].nota);

            continue;
        }

        if(opcao == 3) {
            char nome[101] = {'\0'};
            printf("Insira o nome completo: ");

            fflush(stdin);
            fgets(nome, 101, stdin);

            fflush(stdin);
            int aluno = -1;
            for(int i = 0; i < cAlunos; i++) {
                if(strcmp(nome, alunos[i].nome) != 0) continue;

                aluno = i;
                break;
            }

            if(aluno == -1) {
                printf("O aluno nao foi encontrado no registro.\n");
                continue;
            }

            printf("Informacoes sobre %s - Idade: %d\n - Nota: %0.2f\n\n", alunos[aluno].nome, alunos[aluno].idade, alunos[aluno].nota);

            continue;
        }

        if(opcao == 4) break;

        printf("Opcao invalida.\n");
    }
    
    _alunos = fopen("alunos.data", "wb");
    fwrite(alunos, sizeof(Aluno), cAlunos, _alunos);
    fclose(_alunos);

    return 0;
}