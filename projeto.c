#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

// Implementação das funções

void menu(){
    printf("   ==================================================\n");
    printf("   Bem vindo ao sistema de gerenciamento de registros\n");
    printf("   ==================================================\n");

    printf("\t+------ Escolha a opção desejada ------+\n");
    printf("\t|\t 1 - Novo registro             |\n");
    printf("\t|\t 2 - Ler registro              |\n");
    printf("\t|\t 3 - Remover registro          |\n");
    printf("\t+--------------------------------------+\n");
}

int escolherOpcao(){
    int opcao;

    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}