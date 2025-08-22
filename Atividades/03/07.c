// Exercicio 7 • Registro de Alunos: Crie um programa que permita ao usuário cadastrar alunos (nome,
// idade e nota) em um arquivo binário. O programa deve ter opções para adicionar novos
// alunos, listar todos os alunos e buscar um aluno pelo nome.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define NAME_SIZE 100

typedef struct aluno {
    char nome[NAME_SIZE];
    int idade;
    float nota;
} Aluno;

FILE *_alunos = NULL;
char *filePath = "alunos.data";

Aluno *alunos = NULL;
int alunosSize = 0;

void cadastrarAluno() {
    // Se o vetor alunos estiver incorretamente configurado,
    // encerrar o programa.
    if(alunos == NULL) exit(1);

    // Aumente o vetor alunos para acomodar o novo aluno.
    // Caso a alocação falhe, encerre o programa.
    alunosSize++;
    alunos = (Aluno *) realloc(alunos, alunosSize * sizeof(Aluno));
    if(alunos == NULL) {
        printf("Falha na alocação de memória.");
        exit(1);
    }

    int ai = alunosSize - 1; // índice do novo aluno

    // Obtém o nome completo do aluno.
    printf("\n(Aluno %d)\n Nome: ", alunosSize);
    fflush(stdin);
    fgets(alunos[ai].nome, NAME_SIZE, stdin);
    alunos[ai].nome[strcspn(alunos[ai].nome, "\r\n")] = '\0'; // Remove o caractere '\n' do final do nome.

    // Obtém a idade do aluno.
    printf(" Idade: ");
    fflush(stdin);
    scanf("%d", &alunos[ai].idade);

    // Obtém a nota do aluno.
    printf(" Nota: ");
    fflush(stdin);
    scanf("%f", &alunos[ai].nota);

    printf("Novo aluno adicionado ao registro.\n\n");
    
    return;
}

void listarAlunos() {
    // Se o vetor alunos estiver incorretamente configurado,
    // encerrar o programa.
    if(alunos == NULL) exit(1);

    // Se não tiver alunos no registro, retorne.
    if(alunosSize == 0) {
        printf("Não tem alunos no registro.\n\n");
        return;
    }

    // Para cada aluno cadastrado, imprima seus dados.
    putchar('\n');
    for(int i = 0; i < alunosSize; i++)
        printf("%d - %s (%da)\n Nota: %.2f\n\n", i + 1, alunos[i].nome, alunos[i].idade, alunos[i].nota);

    // Esperar usuário para continuar execução.
    printf("Aperte qualquer tecla para voltar ao menu.\n");
    fflush(stdin);
    getchar();

    return;
}

void buscarAluno() {
    // Se o vetor alunos estiver incorretamente configurado,
    // encerrar o programa.
    if(alunos == NULL) exit(1);

    // Se não tiver alunos no registro, retorne.
    if(alunosSize == 0) {
        printf("Não tem alunos no registro.\n\n");
        return;
    }

    char nome[NAME_SIZE] = {'\0'};

    // Obtém do usuário o nome a ser procurado no registro.
    printf("\nNome: ");
    fflush(stdin);
    fgets(nome, NAME_SIZE, stdin);
    nome[strcspn(nome, "\r\n")] = '\0';

    // Verifica para cada aluno no registro se bate com o nome buscado.
    // Se bater, imprima o nome do aluno e retorne a função.
    for(int i = 0; i < alunosSize; i++) {
        if(strncmp(nome, alunos[i].nome, NAME_SIZE) != 0) continue;

        printf("%d - %s (%da)\n Nota: %.2f\n\n", i + 1, alunos[i].nome, alunos[i].idade, alunos[i].nota);

        // Esperar usuário para continuar execução.
        printf("Aperte qualquer tecla para voltar ao menu.");
        fflush(stdin);
        getchar();

        return;
    }

    printf("Aluno não encontrado no registro.\n\n");
    return;
}

void salvarArquivo(int sig) {
    // Se não tiver alunos no registro, encerre o programa.
    if(alunosSize == 0) exit(0);

    // Tenta abrir o arquivo para salvar,
    // caso não consiga, encerre o programa.
    if(_alunos != NULL) fclose(_alunos);

    _alunos = fopen(filePath, "wb");
    if(_alunos == NULL) exit(1);

    // Salva os alunos no arquivo, e o fecha.
    fwrite(alunos, sizeof(Aluno), alunosSize, _alunos);
    fclose(_alunos);

    // Encerra o programa.
    puts("Arquivo salvo.");
    exit(0);
}

void lerArquivo() {
    // Tenta abrir o arquivo especificado para leitura,
    // caso não consiga, inicialize o vetor alunos e retorne.
    _alunos = fopen(filePath, "rb");
    if(_alunos == NULL) {
        alunos = calloc(1, sizeof(Aluno));
        if(alunos == NULL) {
            printf("Erro ao alocar memória.");
            exit(1);
        }

        return;
    }

    // Verifique quantos alunos tem no registro.
    for(; fgetc(_alunos) != EOF; alunosSize++);
    alunosSize /= sizeof(Aluno);

    // Aloque o vetor alunos para armazena-los na memória
    alunos = calloc(alunosSize, sizeof(Aluno));
    if(alunos == NULL) {
        printf("Erro ao alocar memória.");
        exit(1);
    }

    // Leia o registro de alunos e armazene na memória.
    rewind(_alunos);
    fread(alunos, sizeof(Aluno), alunosSize, _alunos);
    fclose(_alunos);
    _alunos = NULL;

    return;
}

int main(int argc, char **argv) {
    // Caso o usuário tente fechar o programa por CTRL+C,
    // salve automáticamente os alunos registrados.
    signal(SIGINT, salvarArquivo);

    // Caso o usuário tenha especificado um arquivo,
    // troque a variável global do nome.
    if(argc > 1) filePath = argv[1];

    lerArquivo();

    int finalizarExecucao = 0;

    do {
        int opcao = 0;

        fflush(stdin);
        printf("Existem %d aluno(s) no registro. O que deseja fazer?\n1- Cadastrar novo aluno\n2- Listar todos os alunos\n3- Buscar aluno pelo nome\n4- Salvar e sair.\n\n> ", alunosSize);
        char bfr[100] = {'\0'};
        fgets(bfr, 100, stdin);

        opcao = atoi(bfr);

        if(opcao == 1) {
            cadastrarAluno();
            continue;
        } else if(opcao == 2) {
            listarAlunos();
            continue;
        } else if(opcao == 3) {
            buscarAluno();
            continue;
        } else if(opcao == 4) {
            finalizarExecucao = 1;
            continue;
        }

        if(strcmp("", bfr) == 0 && opcao == 0) break;

        puts("Opção inválida.");

    } while(finalizarExecucao == 0);

    salvarArquivo(0);

    return 0;
}