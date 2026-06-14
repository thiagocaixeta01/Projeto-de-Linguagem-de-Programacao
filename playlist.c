#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Implementação das funções
typedef struct No {
    Musica musica;
    struct No *prox;
}Track;

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


void inicializarPlaylist(Track **inicio_lista, Track **fim_lista){

    *inicio_lista = NULL;
    *fim_lista = NULL;

}
void adicionarMusica(Track **inicio, Track **fim, Musica m){
    
    Track *nova_track = (Track*)malloc(sizeof(Track));

    if(nova_track == NULL){
        printf("Erro na alocação de memória!\n");
        return;
    }

    nova_track->musica = m;
    nova_track->prox = NULL;

     if(*inicio == NULL){
        *inicio = nova_track;
    }else{
        (*fim)->prox = nova_track;
    }

    *fim = nova_track;

    printf("Nova música adcionada à Playlist!\n");

}
void listarMusicas(Track *inicio){

    Track *atual = inicio;

    while(inicio != NULL){
        printf("Título: %s || Artista: %s || Album: %s || Ano: %d", atual->musica.titulo, atual->musica.artista, atual->musica.album, atual->musica.ano);
        atual = atual->prox;
    }

    printf("\n");

}

void removerMusica(Track **inicio, char titulo[], char artista[], char album, int ano){

    if(*inicio == NULL){
        printf("Playlist Vazia!\n");
        return;
    }

    Track *atual = *inicio;
    Track *posterior = atual->prox;

    while(posterior != NULL){
        if(titulo == atual->musica.titulo && artista == atual->musica.artista && album == atual->musica.album && ano == atual->musica.ano){
            atual = posterior;
            posterior = posterior->prox;

            printf("Musica %s removida da Playlist!\n", atual->musica.titulo);
            free(atual);
           
            }else{
            printf("Música %s não encontrada!\n", titulo);
            }
    }
}

void liberarPlaylist(Track **inicio){

    Track *atual = inicio;
    Track *posterior = atual->prox;

    if(atual == NULL){
        printf("Playlist já está vazia!\n");
        return;
    }

    while(atual != NULL){
        fee(atual);
        atual = posterior;
        posterior = posterior->prox;
    }

    (*inicio) = NULL;
}