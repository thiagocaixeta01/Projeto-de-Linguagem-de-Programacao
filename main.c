#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Chamada das funções e desenvolvimento do programa principal

int main() {
    setlocale(LC_ALL, "Portuguese");

    Track *inicio, *fim;
    inicializarPlaylist(&inicio, &fim);

    Musica m;
    char titulo_busca[100];

    int opcao;
    do {
        menu();
        opcao = escolherOpcao();

        switch (opcao) {
            case 1:
                dadosMusica(&m);
                adicionarMusica(&inicio, &fim, m);
                
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                
                break;
            
            case 2:
                listarMusicas(inicio);
                
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                
                break;
            
            case 3:
                printf("Digite o título da música a ser removida: ");
                fgets(titulo_busca, sizeof(titulo_busca), stdin);
                titulo_busca[strcspn(titulo_busca, "\n")] = '\0';

                removerMusica(&inicio, &fim, titulo_busca);
                
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                
                break;

            case 0:
                printf("Encerrando a playlist...\n");
                break;

            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }

    } while (opcao != 0);

    
    liberarPlaylist(&inicio, &fim);
    
    return 0;
}