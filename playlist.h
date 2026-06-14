#ifndef PLAYLIST_H
#define PLAYLIST_H

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

void inicializarPlaylist(Track **inicio_lista, Track **fim_lista);
void adicionarMusica(Track **inicio, Track **fim, Musica m);
void dadosMusica(Musica *m);
void listarMusicas(Track *inicio);
void removerMusica(Track **inicio, Track **fim, char titulo_busca[]);

void salvarPlaylist(Track *inicio, const char *nome_arquivo);
void carregarPlaylist(Track **inicio, Track **fim, const char *nome_arquivo);

void liberarPlaylist(Track **inicio, Track **fim);


#endif