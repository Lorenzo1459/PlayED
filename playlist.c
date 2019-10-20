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

void InserePlaylist(Playlists *playlists,char *nomePlaylist){
  //insere uma playlist vazia na lista
  Playlist *nova=InicializaPlaylist(nomePlaylist);
  if(playlists->prim==NULL){
    playlists->prim=playlists->ult=nova;
  }
  else{
    playlists->ult->prox=nova;
    playlists->ult=nova;
  }
  printf("Cria playlist : %s\n",nova->nome_playlist);
}

void InserePlaylist2(Playlists *playlists,Playlist* p){
  //insere uma playlist vazia na lista
  if(playlists->prim==NULL){
    playlists->prim=playlists->ult=p;
  }
  else{
    playlists->ult->prox=p;
    playlists->ult=p;
  }
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
    // puts("\n\n\n");
    printf("ImprimePlaylists() ::: %s\n", aux->nome_playlist);
    ImprimePlaylist(aux);
    aux = aux->prox;
  }
}
void LeArqMusicas(char *nomePlaylist,Playlist *playlist){
  FILE *arq=fopen(nomePlaylist,"r");
  // puts(nomePlaylist);
  char c,nomeMusica[200],nomeArtista[40];
  int n=0;
  if(arq != NULL)
  {

    while(c != EOF){
      c=fgetc(arq);
      //printf("%c",c);
      while(c != '-'){
        nomeArtista[n]=c;
         n++;
         c=fgetc(arq);
        }
       nomeArtista[n]='\0';
      // puts(nomeArtista);
      n=0;
      if(c== '-'){
         c=fgetc(arq);
      }
       while(c  != '\n'&& c !=EOF){
         nomeMusica[n]=c;
        n++;
        c=fgetc(arq);

      }
        if(c!=EOF){
        nomeMusica[n]='\0';
        // puts(nomeMusica);
        InsereMusica(InicializaMusica(nomeArtista,nomeMusica),playlist);
        memset(nomeMusica,0,strlen(nomeMusica));
        memset(nomeArtista,0,strlen(nomeArtista));
        n=0;
        }
    }
      nomeMusica[n]='\0';
      // puts(nomeMusica);
      InsereMusica(InicializaMusica(nomeArtista,nomeMusica),playlist);
      memset(nomeMusica,0,strlen(nomeMusica));
      memset(nomeArtista,0,strlen(nomeArtista));
      c='c';//reseta o c pra n guardar o  EOF
      n=0;
  }
  else{puts("não abriu");
  }
fclose(arq);
}
void leInfoPlaylists(Playlists *playlists){
  Playlist *aux=playlists->prim;
  while(aux != NULL){
    LeArqMusicas(aux->nome_playlist,aux);
    aux=aux->prox;
  }
}

void RefatoraPlaylistsDePessoa(Playlists *playlists){
  Playlist* aux=playlists->prim;
  while (aux != NULL) {
    UnePlaylists(playlists,RefatoraUmaPlaylist(aux));
    aux = aux->prox;
  }
}



Playlists* RefatoraUmaPlaylist(Playlist* p){
  TcelulaM* aux = p->prim;
  TcelulaM* aux2 = p->prim;
  Playlists* novalista = InicializaPlaylists();
  while (aux != NULL) {
    Playlist* nova = InicializaPlaylist(aux->musica->artista);
    while (aux2 != NULL) {
      if (strcmp(aux->musica->artista,aux2->musica->artista) == 0) {
        InsereMusica(retiraMusica(aux2->musica,p),nova); // loop infinito por causa dessa linha
      }
      aux2 = aux2->prox;
    }
    InserePlaylist2(novalista,nova);
    aux = aux->prox;
  }
  //liberar a memoria da playlist p
  return novalista;
}

Playlists* UnePlaylists(Playlists *playlists,Playlists* playlists2){
  Playlist* aux = playlists2->prim;
  while (aux != NULL) {
    InserePlaylist2(playlists,aux);
    //implementar logica de ^ remocao de playlist de uma lista de playlists
    aux = aux->prox;
  }
  return playlists;
}

Musica* retiraMusica(Musica *musica,Playlist* playlist){
  TcelulaM *aux=playlist->prim,*aux2=playlist->prim;
  Musica *auxresultado;
  while(aux != NULL){
    if(strcmp(aux->musica->artista,musica->artista)==0 && strcmp(aux->musica->artista,playlist->prim->musica->artista)==0){
      auxresultado=aux->musica;
      playlist->prim=aux->prox;
      return auxresultado;
    }
    if(strcmp(aux->musica->artista,musica->artista)==0){
      auxresultado=aux->musica;
      aux2=aux->prox;
      return auxresultado;
    }
    aux2=aux;
    aux=aux->prox;

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
