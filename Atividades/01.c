// ATIVIDADE 01 - Algorítimos e Técnicas de Programação II - 04/08/2025
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// a) Elaborar o registro que represente um hóspede do Spa. Declarar uma variável que
// permita cadastrar até 20 hóspedes.
typedef struct hospede {
    bool alta;
    int pesoEntrada;
    int pesoSaida;
    char nome[101];
    int diasTratamento;
    int caloriasDiarias[30];

} Hospede;

Hospede *hospedes[20]; // Array com todos os hospedes
int nHospedes = 0;     // Inteiro para armazenar o tamanho da array

// b) Fazer um módulo (procedimento ou função) que permita ao usuário cadastrar, via teclado,
// todos os dados de um paciente, exceto o peso ao sair.
int registrarPaciente() {
    if(nHospedes >= 19) { // Se o spa estiver lotado, não é possivel cadastrar um novo hóspede.
        printf("O Spa esta lotado.\n");
        return 1;
    }

    Hospede *hospede = malloc(sizeof(Hospede)); // Aloca o espaço de memória para armazenar os dados de um hóspede
    if(hospede == NULL) return 1;

    hospedes[nHospedes] = hospede; // Armazena o hóspede no array global

    printf("(Ficha numero %d)\nNome: ", nHospedes + 1); // Obtem o nome do paciente
    char c = fgetc(stdin); int i = 0;
    for(c = '\0'; i < 100 && c != '\n'; i++) { // Enquanto o usuário não apertar enter, obter o próximo caractere e colocar na string.
        c = fgetc(stdin);
        hospede->nome[i] = c;
    }
    hospede->nome[i + 1] = '\0'; // Finaliza a string com NULL

    // Obtem o peso ao entrar
    printf("Peso ao entrar (g): ");
    scanf("%d", &hospede->pesoEntrada);

    // Obtem quantos dias o paciente estará no Spa
    printf("Qtde Dias Tratamento: ");
    scanf("%d", &hospede->diasTratamento);

    // Caso a quantidade de dias de tratamento esteja fora do escopo, defina para um valor padrão.
    if(hospede->diasTratamento > 30) hospede->diasTratamento = 30;
    else if(hospede->diasTratamento < 1) hospede->diasTratamento = 1;

    // Obtem o número de calorias que o hóspede pode ingerir em cada dia.
    printf("Quantidade de calorias que podem ser ingeridas por dia de tratamento:\n");
    for(int i = 0; i < hospede->diasTratamento; i++) {
        printf("Dia %d: ", i + 1);
        scanf("%d", &hospede->caloriasDiarias[i]);
    }

    // Define o hóspede como não em alta.
    hospede->alta = false;

    nHospedes++;

    return 0;
}

// c) Fazer um módulo que permita ao usuário, através do número da ficha do paciente, dar
// alta ao paciente (o que significa cadastrar seu peso ao sair, em gramas, e escrever quanto
// peso foi perdido, em quilos). Deve-se marcar na ficha que o paciente teve alta (isso não
// significa excluir o registro do paciente)
int darAlta() {
    
    // Obtem o número da ficha do paciente.
    int ficha = 0;
    printf("Numero da ficha: ");
    scanf("%d", &ficha);
    ficha--;

    // Verificação de se o número da ficha é válido ou se o paciente já teve alta.
    if(ficha < 0 || ficha >= nHospedes) {
        printf("Numero da ficha invalido.\n");
        return 1;
    } else if(hospedes[ficha]->alta == true) {
        printf("O paciente ja tem alta.\n");
        return 2;
    }

    // Recupera o hóspede do array global.
    Hospede *hospede = hospedes[ficha];

    // Define o hóspede como tendo alta.
    hospede->alta = true;

    // Obtem do usuário o seu peso ao sair.
    printf("Peso ao sair (g): ");
    scanf("%d", &hospede->pesoSaida);

    // Imprime no terminal quantos kilos o paciente perdeu.
    printf("O paciente perdeu %0.3fkg.\n", (float) (hospede->pesoEntrada - hospede->pesoSaida) / 1000.0f);

    return 0;
}

// d) Escrever o programa principal que permita que o usuário selecione uma das opções:
// cadastrar ou dar baixa em pacientes. Enquanto o usuário não desejar encerrar a execução,
// o programa deve permitir que ele cadastre ou dê baixa em pacientes.
int main(void) {
    
    bool fim = false; // Variável para definir quando o programa for fechar.

    while(!fim) {
        // Obtem a opção do usuário
        int opcao = 0;
        printf("\n1 - Registrar Paciente\n2 - Dar Baixa em Paciente\n3 - Sair\nSelecione sua opcao: ");
        scanf("%d", &opcao);

        // Executa a opção correspondente, e nenhuma caso seja inválida.
        if(opcao == 1) {
            registrarPaciente();
        } else if(opcao == 2) {
            darAlta();
        } else if(opcao == 3) {
            fim = true;
        } else {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}