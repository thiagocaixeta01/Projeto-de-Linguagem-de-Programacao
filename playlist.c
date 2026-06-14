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
    printf("\n");
    printf("    ================================================\n");
    printf("    Bem vindo ao sistema de gerenciamento de músicas\n");
    printf("    ================================================\n");

    printf("\n\t+------ Escolha a opção desejada ------+\n");
    printf("\t|\t 1 - Adicionar Música          |\n");
    printf("\t|\t 2 - Listar Músicas            |\n");
    printf("\t|\t 3 - Remover Música            |\n");
    printf("\t|\t 0 - Sair                      |\n");
    printf("\t+--------------------------------------+\n");
}

int escolherOpcao(){
    int opcao;

    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

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

    printf("\nMúsica (%s) adicionada à playlist com sucesso!\n", m.titulo);

}

void dadosMusica(Musica *m){

    printf("\t-> Digite o título da música: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("\t-> Digite o nome do artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("\t-> Digite o nome do álbum: ");
    fgets(m->album, sizeof(m->album), stdin);
    m->album[strcspn(m->album, "\n")] = '\0';

    printf("\t-> Digite o ano de lançamento: ");
    scanf("%d", &m->ano);
    getchar();

}

void listarMusicas(Track *inicio){

    Track *atual = inicio;

    if(atual == NULL){
        printf("\nA Playlist está vazia!\n");
        return;
    }

    while(atual != NULL){
        printf("Título: %s || Artista: %s || Album: %s || Ano: %d", atual->musica.titulo, atual->musica.artista, atual->musica.album, atual->musica.ano);
        atual = atual->prox;
    }

    printf("\n");
}

void removerMusica(Track **inicio, Track **fim, char titulo_busca[]){

    if(*inicio == NULL){
        printf("\nPlaylist Vazia!\n");
        return;
    }

    Track *atual = *inicio;
    Track *anterior = NULL;

    while (atual != NULL && strcmp(atual->musica.titulo, titulo_busca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nMúsica (%s) não foi encontrada na playlist!\n", titulo_busca);
        return;
    }

    if (anterior == NULL) {
        *inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    if (atual == *fim) {
        *fim = anterior;
    }
    
    free(atual);
    
    printf("\nMúsica (%s) removida da playlist!\n", titulo_busca);

}

void liberarPlaylist(Track **inicio, Track **fim){

    Track *atual = *inicio;
    Track *proximo_no;

    while(atual != NULL){
        proximo_no = atual->prox;
        free(atual);
        atual = proximo_no;
    }

    *inicio = NULL;
    *fim = NULL;
}