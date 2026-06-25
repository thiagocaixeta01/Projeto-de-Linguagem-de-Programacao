#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// Chamada das funções e desenvolvimento do programa principal

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    char *arquivo = "Playlist.bin";
    Track *inicio, *fim;
    inicializarPlaylist(&inicio, &fim);

    loopMenu();
    
    liberarPlaylist(&inicio, &fim);
    
    return 0;
}