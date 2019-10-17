#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"pessoa.h"

struct musica{
  char* nome; // Nome da musica
  char* artista; // Nome do artista
};
struct tcelulam{
  Musica *musica; // Musica (conteudo)
  TcelulaM *prox; // Apontador para proxima musica
};

struct playlist{
  char* nome_playlist; // Nome da playlist atual
  Playlist *prox; // Apontador para a proxima playlist
  TcelulaM *prim,*ult; //Sentinela da lista de musicas
};

struct playlists{
  Playlist *prim,*ult; // Sentinela da lista de playlists
};

Playlists* InicializaPlaylists(){
  Playlists *playlists = malloc(sizeof(Playlists));
  playlists->prim = playlists->ult= NULL;
}

Musica* InicializaMusica(char* artista, char* nome){
  Musica* mus = (Musica*)malloc(sizeof(Musica));
  mus->artista = strdup(artista);
  mus->nome = strdup(nome);
  return mus;
}

Playlist* InicializaPlaylist(char *nome){
  Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
  playlist->nome_playlist = strdup(nome);
  playlist->prox = NULL;
  playlist->prim = playlist->ult = NULL;
  return playlist;
}

void CriaPlaylist(Playlists *playlists,char *nomePlaylist){
  //insere uma playlist vazia na lista
  Playlist *nova=InicializaPlaylist(nomePlaylist);
  if(playlists->prim==NULL){
    playlists->prim=playlists->ult=nova;
  }
  else{
    playlists->ult->prox=nova;
    playlists->ult=nova;
  }
  printf("%s\n",nova->nome_playlist);
}

void InsereMusica (Musica* mus, Playlist* lista){
 // Insere dada música na Playlist desejada
 TcelulaM* nova = (TcelulaM*)malloc(sizeof(TcelulaM));
 nova->musica = mus;
 nova->prox = NULL;
 if (lista->prim == NULL) {
   lista->prim = lista->ult = nova;
 }
 else{
   lista->ult->prox = nova;
   lista->ult = nova;
 }
}

void ImprimePlaylist (Playlist* p){
  // Imprime a playlist desejada
  TcelulaM* aux = p->prim;
  while (aux != NULL) {
    printf("%s - ",aux->musica->artista);
    printf("%s\n", aux->musica->nome);
    aux = aux->prox;
  }
}

void ImprimePlaylists (Playlists* p){
  // Imprime a lista de playlists
  Playlist* aux = p->prim;
  while (aux != NULL) {
    printf("%s\n", aux->nome_playlist);
    ImprimePlaylist(aux);
    aux = aux->prox;
  }
}









//funcoes de retorno p/ escopo caso necessarias
// Playlist* retornaPrimeiro(Playlists* p){
//   return p->prim;
// }
//
// Playlist* retornaProximo(Playlist* p){
//   return p->prox;
// }
