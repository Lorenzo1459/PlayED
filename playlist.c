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
  // printf("Cria playlist : %s\n",nova->nome_playlist);
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
    printf("-------------%s------------\n", aux->nome_playlist);
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
       nomeArtista[n-1]='\0';
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
  // printf("entrei Refatora TODAS DA PESSOA\n");
  Playlist* aux = playlists->prim;
  Playlist* aux2 = playlists->ult;
  int n = 0;
  do{
    // printf("NUMERO = %d\n", ++n);
    if(aux == aux2)
    UnePlaylists(playlists,RefatoraUmaPlaylist(aux));
    else{
    UnePlaylists(playlists,RefatoraUmaPlaylist(aux));
    aux = aux->prox;
    }
  }
  while (aux != aux2);
  UnePlaylists(playlists,RefatoraUmaPlaylist(aux));
}

static int tamanhoplaylist(Playlist* p){
  TcelulaM* aux = p->prim;
  int n =0;
  while (aux != NULL)
  {
    n++;
    aux = aux->prox;
  }
  return n;
}

int existeNaPlay(char *nome,Playlists *playlists){
  Playlist *aux=playlists->prim;
  while(aux!=NULL){
    if(strcmp(nome,aux->nome_playlist)){
      return 1;
    }
  aux=aux->prox;
  }
  return 0;
}

Playlists* RefatoraUmaPlaylist(Playlist* p){
  if(p != NULL){
  TcelulaM* aux = p->prim;
  TcelulaM* aux2 = aux;
  TcelulaM* auxFree;
  Musica *outroAux;
  int atualizador = 0;
  Playlists* novalista = InicializaPlaylists();
  while (aux != NULL) {
    Playlist* nova = InicializaPlaylist(aux->musica->artista);
    aux2=p->prim;
    while (aux2 != NULL) {
      if (strcmp(aux->musica->artista,aux2->musica->artista) == 0) {
        outroAux=SeparaCelulaM(retiraMusica(aux2->musica,p));
        InsereMusica(outroAux,nova); // loop infinito por causa dessa linha
        // aux2=p->prim;
        // free(auxFree);
      }
      aux2 = aux2->prox;
    }
    InserePlaylist2(novalista,nova);
    auxFree=aux;
    aux = aux->prox;
    free(auxFree);

  }
  //liberar a memoria da playlist p
  return novalista;
  }
}

Playlists* UnePlaylists(Playlists *playlists,Playlists* playlists2){
  Playlists* pl = InicializaPlaylists();
  Playlist* aux = playlists2->prim;
  while (aux != NULL) {
    InserePlaylist2(playlists,aux);
    //implementar logica de ^ remocao de playlist de uma lista de playlists
    aux = aux->prox;
  }
  return playlists;
}

TcelulaM* retiraMusica(Musica *musica,Playlist* playlist){
  TcelulaM *aux=playlist->prim,*aux2=NULL;
  TcelulaM *auxresultado;
  while(aux != NULL){
    if(strcmp(aux->musica->artista,musica->artista)==0 && strcmp(aux->musica->artista,playlist->prim->musica->artista)==0){
      auxresultado=aux;
      if (playlist->prim == playlist->ult) {
        playlist->ult = NULL;
        playlist->prim = NULL;
      }
      playlist->prim=aux->prox;
      // playlist->ult=NULL;
      // aux=NULL;
      return auxresultado;
    }
    else if(strcmp(aux->musica->artista,musica->artista)==0){
      auxresultado=aux;
      aux2->prox=aux->prox;
      return auxresultado;
    }
    aux2=aux;
    aux=aux->prox;

  }
  return NULL;
}

Musica* SeparaCelulaM(TcelulaM *celula){
  Musica *guarda=InicializaMusica(celula->musica->artista,celula->musica->nome);
  //free(celula->musica->artista);
  //free(celula->musica->nome);
  //free(celula->)
  //free(celula);
  return guarda;
}

void RetiraPlayVazias(Playlists *playlists){
  Playlist *aux=playlists->prim,*aux2;
  Playlist *auxFree= NULL ;
  while(aux != NULL){
    auxFree = NULL;
    // puts(aux->nome_playlist);
    if(aux->prim == NULL ){
      // puts("entrei");
      if(aux==playlists->prim){
        auxFree=aux;
        playlists->prim=aux->prox;
        aux=aux->prox;
        free(auxFree);

      }
      else{
        auxFree=aux;
        aux2->prox=aux->prox;
        aux=aux->prox;
        free(auxFree);

      }


  //puts(aux2->nome_playlist);

  }

  else{
    aux2=aux;
    aux=aux->prox;
  }

  }

  }



int num_playlists(Playlists* p){
  Playlist* aux = p->prim;
  int n = 0;
  while (aux != NULL) {
    n++;
    aux = aux->prox;
  }
  return n;
}




//funcoes de retorno p/ escopo caso necessarias
Playlist* retornaPrimeiro(Playlists* p){
  return p->prim;
}

Playlist* retornaProximo(Playlist* p){
  return p->prox;
}

char* retornaNome(Playlist* p){
  return p->nome_playlist;
}

TcelulaM* retornaPrimeiraCel(Playlist* p){
  return p->prim;
}

TcelulaM* retornaProxCel(TcelulaM* p){
  return p->prox;
}
char* retornaNomeMusica(TcelulaM* cel){
  return cel->musica->nome;
}