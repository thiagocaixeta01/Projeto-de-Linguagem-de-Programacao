#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Implementação das funções

void menu(){
    printf("   ==================================================\n");
    printf("   Bem vindo ao sistema de gerenciamento de registros\n");
    printf("   ==================================================\n");

    printf("\t+------ Escolha a opção desejada ------+\n");
    printf("\t|\t 1 - Nova Música               |\n");
    printf("\t|\t 2 - Listar Músicas            |\n");
    printf("\t|\t 3 - Remover Música            |\n");
    printf("\t+--------------------------------------+\n");
}

int escolherOpcao(){
    int opcao;

    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}