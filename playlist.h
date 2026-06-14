#ifndef PROJETO_H
#define PROJETO_H

// Declaração da struct

typedef struct {
    char titulo[100];
    char artista[50];
    char album[50];
    int ano;
} Musica;

typedef struct No Track;
// Declaração das funções

void menu();
int escolherOpcao();

void inicializarPlaylist(Track *inicio_lista, Track *fim_lista);
void adicionarMusica(Track **inicio, Track **fim, Musica m);
void listarMusicas(Track *inicio);
void removerMusica(Track **inicio, char titulo[], char artista[], char album, int ano);

void liberarPlaylist(Track **inicio);


#endif