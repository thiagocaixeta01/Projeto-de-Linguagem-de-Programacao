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

Track *lista = NULL;

void menu(){

    int opcao;

    do{
    printf("   ==================================================\n");
    printf("   Bem vindo ao sistema de gerenciamento de registros\n");
    printf("   ==================================================\n");

    printf("\t+------ Escolha a opção desejada ------+\n");
    printf("\t|\t 1 - Novo registro             |\n");
    printf("\t|\t 2 - Ler registro              |\n");
    printf("\t|\t 3 - Remover registro          |\n");
    printf("\t+--------------------------------------+\n");

    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                
                printf("\nAdicionando música...\n");

                break;
            
            case 2:
                
                printf("\nLendo música...\n");

                break;
            
            case 3:
                printf("\nDigite o título da música a ser removida: ");
                
                printf("\nRemovendo música...\n");

                break;

            case 0:
                printf("\nEncerrando a playlist...\n");
                break;

            default:
                printf("\nOpção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }

    } while (opcao != 0);
    
}


void carregarPlaylist(char *playlist){

    FILE *pl = fopen(playlist, "rb");
    if(pl == NULL){
        printf("Arquivo %s não encontrado!\n", playlist);
        return;
    }

    Musica m;
    while(fread(&m, sizeof(Musica), 1, pl) == 1){
        Track *nova = (Track*)malloc(sizeof(Track));
        nova->musica = m;
        nova->prox = lista;
        lista = nova;
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

    printf("\t-> Título: ");
    fgets(m->titulo, sizeof(m->titulo), stdin);
    m->titulo[strcspn(m->titulo, "\n")] = '\0';

    printf("\t-> Artista: ");
    fgets(m->artista, sizeof(m->artista), stdin);
    m->artista[strcspn(m->artista, "\n")] = '\0';

    printf("\t-> Album: ");
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
        printf("Removendo a música de índice [%d]...\n", atual->musica.indice);
        *lista = atual->prox;
        free(atual);
        return;

        int conta_musica = contarLista(*lista);
        Track *percorre = *lista;
        while(percorre != NULL){
            percorre->musica.indice = conta_musica--;
            percorre = percorre->prox;
        }
    }

    Track *posterior = atual->prox;

    while(posterior != NULL && posterior->musica.indice != indice){
        atual = posterior;
        posterior = posterior->prox;
    }

    if(posterior != NULL){
        printf("Removendo a música de índice [%d]...\n", indice);
        atual->prox = posterior->prox;
        free(posterior);
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
    printf("Track: %d || Titulo: %s || Artista: %s || Álbum: %s || Ano: %d\n", 
            atual->musica.indice, 
            atual->musica.titulo, 
            atual->musica.artista, 
            atual->musica.album, 
            atual->musica.ano);
    }
}

void liberarPlaylist(Track **lista){

    Track *atual = *lista;

    if(atual == NULL){
        printf("Playlist já está vazia!\n");
        return;
    }

    while(atual != NULL){

        Track *posterior = atual->prox;
        free(atual);
        atual = posterior;
    }

    (*lista) = NULL;
    printf("fechando...\n");
}

int main(){

    //menu();
    char *arquivo = "playlist.bin";

    carregarPlaylist(arquivo);
    int conta = contarLista(lista);
    adicionarMusica(&lista, conta);
    conta = contarLista(lista);
    adicionarMusica(&lista, conta);
    conta = contarLista(lista);
    adicionarMusica(&lista, conta);
    exibirPlaylist(lista);
    removerMusica(&lista, 4);
    exibirPlaylist(lista);
    removerMusica(&lista, 6);
    exibirPlaylist(lista);
    conta = contarLista(lista);
    adicionarMusica(&lista, conta);
    exibirPlaylist(lista);
    liberarPlaylist(&lista);


    return 0;
}