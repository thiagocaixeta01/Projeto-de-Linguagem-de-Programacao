#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Implementa??o das fun??es
typedef struct No {
    Musica musica;
    struct No *prox;
}Track;

void menu(){
    printf("\n");
    printf("    ================================================\n");
    printf("    Bem vindo ao sistema de gerenciamento de m?sicas\n");
    printf("    ================================================\n");

    printf("\n\t+------ Escolha a op??o desejada ------+\n");
    printf("\t|\t 1 - Adicionar M?sica          |\n");
    printf("\t|\t 2 - Listar M?sicas            |\n");
    printf("\t|\t 3 - Remover M?sica            |\n");
    printf("\t|\t 0 - Sair                      |\n");
    printf("\t+--------------------------------------+\n");
}

int escolherOpcao(){
    int opcao;

    printf("\nEscolha uma op??o: ");
    scanf("%d", &opcao);
    getchar();

    return opcao;
}

void loopMenu() {
    Track *inicio, *fim;
    
    int opcao;    
    Musica m;
    char titulo_busca[100];

     do {
        menu();
        opcao = escolherOpcao();

        switch (opcao) {
            case 1:
                dadosMusica(&m);
                adicionarMusica(&inicio, &fim, m);
                break;
                
            case 2:
                listarMusicas(inicio);
                break;
                
            case 3:
                printf("Digite o t?tulo da m?sica a ser removida: ");
                fgets(titulo_busca, sizeof(titulo_busca), stdin);
                titulo_busca[strcspn(titulo_busca, "\n")] = '\0';

                removerMusica(&inicio, &fim, titulo_busca);      
                break;

            case 0:
                printf("Encerrando a playlist...\n");
                break;

            default:
                printf("Op??o inv?lida! Por favor, escolha uma op??o v?lida.\n");
                break;
        }
    } while (opcao != 0);
}

void inicializarPlaylist(Track **inicio_lista, Track **fim_lista){

    *inicio_lista = NULL;
    *fim_lista = NULL;

} 

void adicionarMusica(Track **inicio, Track **fim, Musica m){
    
    Track *nova_track = (Track*)malloc(sizeof(Track));

    if(nova_track == NULL){
        printf("Erro na aloca??o de mem?ria!\n");
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

    printf("\nM?sica (%s) adicionada ? playlist com sucesso!\n", m.titulo);

}

void dadosMusica(Musica *m){

    printf("\t-> Digite o t?tulo da m?sica: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("\t-> Digite o nome do artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("\t-> Digite o nome do ?lbum: ");
    fgets(m->album, sizeof(m->album), stdin);
    m->album[strcspn(m->album, "\n")] = '\0';

    printf("\t-> Digite o ano de lan?amento: ");
    scanf("%d", &m->ano);
    getchar();

}

void listarMusicas(Track *inicio){

    Track *atual = inicio;

    if(atual == NULL){
        printf("\nA Playlist est? vazia!\n");
        return;
    }

    while(atual != NULL){
        printf("T?tulo: %s || Artista: %s || Album: %s || Ano: %d", atual->musica.titulo, atual->musica.artista, atual->musica.album, atual->musica.ano);
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
        printf("\nM?sica (%s) n?o foi encontrada na playlist!\n", titulo_busca);
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
    
    printf("\nM?sica (%s) removida da playlist!\n", titulo_busca);

}

int lerPlaylist(Track *inicio, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Arquivo (%s) n?o entrado!\n", nome_arquivo);
        return 0;
    }

    Track *atual = inicio;
    int total_musicas = 0;
    Musica m;
    while (fread(&m, sizeof(Musica), 1, arquivo) == 1) {
        
        total_musicas++;
    }
    
    fclose(arquivo);
    return total_musicas;
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