#include "projeto.h"

// Implementação das funções

void menu(){
    printf("==================================================\n");
    printf("Bem vindo ao sistema de gerenciamento de registros\n");
    printf("==================================================\n");

    printf("+------ Escolha a opção desejada ------+\n");
    printf("|\t 1 - Novo registro                  |\n");
    printf("|\t 2 - Ler registro                   |\n");
    printf("|\t 3 - Remover registro               |\n");
    printf("+--------------------------------------+\n");
}

int escolherOpcao(){
    int opcao;

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}