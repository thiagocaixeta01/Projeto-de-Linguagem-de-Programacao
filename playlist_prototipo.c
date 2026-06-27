#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica{
    int indice;
    char titulo[100];
    char artista[50];
    char album[50];
    int ano;
}Musica;

typedef struct Track{
    Musica musica;
    struct Track *prox;
}Track;

void carregarPlaylist(char *playlist, Track **lista){

    FILE *pl = fopen(playlist, "rb");
    if(pl == NULL){
        printf("Arquivo %s não encontrado!\n", playlist);
        return;
    }

    Musica m;
    while(fread(&m, sizeof(Musica), 1, pl) == 1){
        Track *nova = (Track*)malloc(sizeof(Track));
        nova->musica = m;
        nova->prox = *lista;
        *lista = nova;
    }

    fclose(pl);
}

void salvarPlaylist(char *playlist, Track *lista) {
    FILE *pl = fopen(playlist, "wb");
    if(pl == NULL) {
        printf("Erro ao salvar o arquivo!\n");
        return;
    }
    Track *atual = lista;
    while(atual != NULL) {
        fwrite(&atual->musica, sizeof(Musica), 1, pl);
        atual = atual->prox;
    }
    fclose(pl);
}

int contarLista(Track *lista){

    int conta_musica = 0;
    Track *atual = lista;

    while(atual != 0){
        conta_musica++;
        atual = atual->prox;
    }

    return conta_musica;
}

void informarMusica(Musica *m){
    
    printf("\t-> Tí­tulo: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("\t-> Artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("\t-> Álbum: ");
    fgets(m->album, sizeof(m->album), stdin);
    m->album[strcspn(m->album, "\n")] = '\0';
    
    printf("\t-> Ano: ");
    scanf("%d", &m->ano);
    getchar();

}

void adicionarMusica(Track **lista, int conta_musica){

    Track *nova = (Track*)malloc(sizeof(Track));
    if(nova == NULL){
        printf("Erro de alocação de memória!\n");
        return;
    }

    Musica ad;
    informarMusica(&ad);

    ad.indice = conta_musica + 1;
    nova->musica = ad;
    nova->prox = *lista;
    (*lista) = nova;

}

void removerMusica(Track **lista, int indice){

    if(*lista == NULL){
        printf("A lista está vazia!\n");
        return;
    }

    Track *atual = *lista;

    if(atual->musica.indice == indice){
        printf("Removendo a música de í­ndice [%d]...\n", atual->musica.indice);
        *lista = atual->prox;
        free(atual);

        int conta_musica = contarLista(*lista);
        Track *percorre = *lista;
        while(percorre != NULL){
            percorre->musica.indice = conta_musica--;
            percorre = percorre->prox;
        }
        return;
    }

    Track *posterior = atual->prox;

    while(posterior != NULL && posterior->musica.indice != indice){
        atual = posterior;
        posterior = posterior->prox;
    }

    if(posterior != NULL){
        printf("Removendo a música de í­ndice [%d]...\n", indice);
        atual->prox = posterior->prox;
        free(posterior);

        int conta_musica = contarLista(*lista);
        Track *percorre = *lista;
        while (percorre != NULL) {
            percorre->musica.indice = conta_musica--;
            percorre = percorre->prox;
        }
    }else{
        printf("Indice de música [%d] não encontrado!\n", indice);
    }
}

void exibirPlaylist(Track *lista){

    Track *atual = lista;

    if(atual == NULL){
        return;
    }else{
    exibirPlaylist(atual->prox);
    printf("Track: %d || Título: %s || Artista: %s || Álbum: %s || Ano: %d\n", 
            atual->musica.indice, 
            atual->musica.titulo, 
            atual->musica.artista, 
            atual->musica.album, 
            atual->musica.ano);
    }
}

void liberarPlaylist(Track **lista){

    Track *atual = *lista;
    while(atual != NULL){
        Track *posterior = atual->prox;
        free(atual);
        atual = posterior;
    }

    *lista = NULL;
}

void menu(Track **lista, char *nome_arquivo){

    int opcao;

    do{
    printf("    =================================================\n");
    printf("    Bem vindo ao sistema de gerenciamento da playlist\n");
    printf("    =================================================\n");

    printf("\t+------ Escolha a opção desejada ------+\n");
    printf("\t|\t 1 - Nova Música               |\n");
    printf("\t|\t 2 - Listar Playlist           |\n");
    printf("\t|\t 3 - Remover Música            |\n");
    printf("\t|\t 0 - Sair                      |\n");
    printf("\t+--------------------------------------+\n");
    
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

        switch (opcao) {
            case 1: {
                int conta = contarLista(*lista);
                adicionarMusica(lista, conta);
                printf("\nAdicionando música...\n");
                break;
            }
            case 2:

                printf("\nLendo músicas...\n");
                exibirPlaylist(*lista);
                break;
            
            case 3:
                if (*lista == NULL) {
                    printf("\nA lista já está vazia!\n");
                    break;
                }
                int indice;
                printf("\nDigite o índice da música a ser removida: ");
                scanf("%d", &indice);
                getchar();
                removerMusica(lista, indice);
                break;

            case 0:
                printf("\nEncerrando a playlist...\n");
                salvarPlaylist(nome_arquivo, *lista);
                break;

            default:
                printf("\nOpção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }

    } while (opcao != 0);
    
}

int main(){

    Track *lista = NULL;
    char *arquivo = "playlist.bin";

    carregarPlaylist(arquivo, &lista);

    menu(&lista, arquivo);

    liberarPlaylist(&lista);


    return 0;
}