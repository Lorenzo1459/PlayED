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
  char c='a',nomeMusica[200],nomeArtista[40];
  int n=0;
  if(arq != NULL)
  {

    while(!feof(arq)){
      c=fgetc(arq);
      if(c==EOF)
      break;
      //printf("%c",c);
      while(c != '-'){ // le o nome do artista
        //printf("%c",c);
        nomeArtista[n]=c;
         n++;
         c=fgetc(arq);
        }
       nomeArtista[n-1]='\0';
      
      n=0;
      if(c== '-'){ // le o nome da musica
         c=fgetc(arq);
      }
       while(c  != '\n'&& c !=EOF){
         nomeMusica[n]=c;
        n++;
        c=fgetc(arq);

      }
        //if(c!=EOF){
        nomeMusica[n]='\0';
        
        puts(nomeArtista);
        InsereMusica(InicializaMusica(nomeArtista,nomeMusica),playlist);
        memset(nomeMusica,0,strlen(nomeMusica));
        memset(nomeArtista,0,strlen(nomeArtista));
        n=0;
        //}
    }
      nomeMusica[n]='\0';
      // puts(nomeMusica);
      //puts(nomeArtista);
      
      // InsereMusica(InicializaMusica(nomeArtista,nomeMusica),playlist);
      // memset(nomeMusica,0,strlen(nomeMusica));
      // memset(nomeArtista,0,strlen(nomeArtista));
      //c='c';//reseta o c pra n guardar o  EOF
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
  
  do{
    // printf("NUMERO = %d\n", ++n);
    if(aux == aux2) // verificação pra quando só tiver 1 playlist
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
  Playlists* novalista = InicializaPlaylists();// cria uma lista de playlists vazia
  
  while (aux != NULL) {
    Playlist* nova = InicializaPlaylist(aux->musica->artista); // cria uma playlist vazia
    aux2=p->prim; // pra sempre percorrer a lista toda
    
    while (aux2 != NULL) {
      if (strcmp(aux->musica->artista,aux2->musica->artista) == 0) { // se for o artista for igual transfere pra lista nova
        TranfereMusica(retiraMusica(aux2->musica,p),nova);
      }
      aux2 = aux2->prox; 
    }
    
    nova->ult->prox=NULL; // pra ultima celula da playlist nova n continuar apontando pro proximo da antiga
    InserePlaylist2(novalista,nova);
    aux = p->prim; // como o primeiro elemento vai ser sempre retirado aux sempre é o primeiro 
  }
 
  return novalista;
  }
}

void TranfereMusica(TcelulaM *celula,Playlist *lista){
  
  if(lista->prim==NULL && lista->ult == NULL){ // se a lista estiver vazia
    lista->prim=celula;
    lista->ult=celula;
  }
  else{
  lista->ult->prox=celula;
  lista->ult=celula;
  }
  
}

Playlists* UnePlaylists(Playlists *playlists,Playlists* playlists2){
    playlists->ult->prox=playlists2->prim;
    playlists->ult=playlists2->ult;
    free(playlists2);

  
  return playlists;
}

TcelulaM* retiraMusica(Musica *musica,Playlist* playlist){
  TcelulaM *aux=playlist->prim,*aux2;
  TcelulaM *auxresultado;
  aux2=aux;
  while(aux != NULL){
    if(strcmp(aux->musica->artista,musica->artista)==0 && strcmp(aux->musica->artista,playlist->prim->musica->artista)==0){
      auxresultado=aux;
      if (playlist->prim == playlist->ult) {
        playlist->ult = NULL;
        playlist->prim = NULL;
      }
      playlist->prim=aux->prox;
      
      return auxresultado;
    }
    else if(strcmp(aux->musica->artista,musica->artista)==0){
      auxresultado=aux;
      aux2->prox=aux->prox;
      return auxresultado;
    }
    aux2=aux;
    aux=aux2->prox;

  }
  return NULL;
}



void RetiraPlayVazias(Playlists *playlists){
  Playlist *aux=playlists->prim,*aux2;
  Playlist *auxFree= NULL ;
  while(aux != NULL){
    auxFree = NULL;
    // puts(aux->nome_playlist);
    if(aux->prim == NULL || aux->ult == NULL ){
      // puts("entrei");
      if(aux==playlists->prim){
        auxFree=aux;
        playlists->prim=aux->prox;
        aux=aux->prox;
        free(auxFree->nome_playlist);
        free(auxFree);

      }
      else{
        auxFree=aux;
        aux2->prox=aux->prox;
        aux=aux->prox;
        free(auxFree->nome_playlist);
        free(auxFree);

      }
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

int ContaSimilaridade(Playlists *pessoa,Playlists*pessoa2){
  Playlist *play1=pessoa->prim,*play2;
  int contador=0;
  TcelulaM *musicaD1,*musicaD2;
  while(play1 != NULL){
    play2=pessoa2->prim;
    while (play2 != NULL)
    {
    musicaD1=play1->prim;
    ;
      if(strcmp(play1->nome_playlist,play2->nome_playlist )==0){
        while(musicaD1!=NULL){
          musicaD2=play2->prim;
          while(musicaD2!=NULL){
            if(strcmp(musicaD1->musica->nome,musicaD2->musica->nome)==0){
              contador++;
            }
          musicaD2=musicaD2->prox;
          }
        musicaD1=musicaD1->prox;
        }
      }
    play2=play2->prox;
    }
  play1=play1->prox;
  }
return contador;
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
void LiberaPlaylists(Playlists* p){
  Playlist *aux=p->prim,*auxPlayFree;
  TcelulaM *auxCelula,*auxCelulaFree;
  while(aux!=NULL){
    auxCelula=aux->prim;
    
    while(auxCelula!=NULL){
      auxCelulaFree=auxCelula;
      auxCelula=auxCelula->prox;
      free(auxCelulaFree->musica->artista);
      free(auxCelulaFree->musica->nome);
      free(auxCelulaFree->musica);
      free(auxCelulaFree);

    }
  auxPlayFree=aux;
  aux=aux->prox;
  free(auxPlayFree->nome_playlist);
  free(auxPlayFree);
  }
}