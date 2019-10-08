#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musica{
  char* nome;
  char* artista;
  /*
  outras informaçoes de musica
  */
};

struct playlist{
  char* nome_playlist;
  Playlist* prox; // Apontador p/ prox (lista sem sentinela)
  Musica* musicas; // Lista de musicas
};

Playlist* InicializaPlaylist(){
  Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
  // playlist->musicas = ?;
  playlist->prox = NULL;
}

void InsereMusica (Musica* mus, Playlist* lista){
 // Insere dada música na Playlist desejada
}

void ImprimePlaylist (Playlist* p){
  // Imprime a playlist desejada
}

Musica* InicializaMusica(char* nome){
  Musica* mus = (Musica*)malloc(sizeof(Musica));
  mus->nome = strdup(nome);
  /*
  alterar se precisar acrescentar informaçoes em *musica*
  */
  return mus;
}
