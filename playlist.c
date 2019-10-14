#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"pessoa.h" 

struct musica{
  char* nome;
  char* artista;
  /*
  outras informaçoes de musica
  */
};
struct tcelulam{
  Musica *musica;
  TcelulaM *prox;
};

struct playlist{
  char* nome_playlist;
  TcelulaM *prim,*ult;
  Playlist *prox;
};

struct playlists{
  Playlist *prim,*ult;
};
Playlists* InicializaPlaylists(){
  Playlists *playlists = malloc(sizeof(Playlists));
  playlists -> prim= playlists -> ult= NULL;
}


Playlist* InicializaPlaylist(char *nome){
  Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
  playlist -> nome_playlist = strdup(nome);
  playlist -> prim = playlist -> ult = NULL;
}
void CriaPlaylist(Playlists *playlists,char *nomePlaylist){
  //insere uma playlist vazia a lista
  Playlist *nova=InicializaPlaylist(nomePlaylist);
  if(playlists->prim==NULL){
    playlists->prim=playlists->ult=nova;
  }
  else{
    playlists->ult->prox=nova;
    playlists->ult=nova;
  }

  
  /////parei aquiiiiiii

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
