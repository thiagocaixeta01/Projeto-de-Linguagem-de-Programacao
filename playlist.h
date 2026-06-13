#ifndef PROJETO_H
#define PROJETO_H

// Declaração da struct

typedef struct {
    char titulo[20];
    char artista[50];
    char album[20];
    int ano;
} musicas;

// Declaração das funções

void menu();
int escolherOpcao();

#endif