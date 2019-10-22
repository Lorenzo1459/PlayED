#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct tcelula{
  Pessoa* pessoa; // Item
  tCelula* prox;
};


struct tipolista{
  tCelula* prim;
  tCelula* ult;
};

struct pessoa{
  char* nome; // Nome da pessoa
  TipoLista* amigos; // Lista de amigos
  Playlists* playlists; // Lista de playlists
};

Pessoa* InicializaPessoa(char* nome){
  Pessoa* p = (Pessoa*)malloc(sizeof(Pessoa));
  p->nome = strdup(nome);
  p->amigos = InicializaListaDePessoas();
  p->playlists = InicializaPlaylists();
  return p;
}

TipoLista* InicializaListaDePessoas(){
  TipoLista* lst = (TipoLista*)malloc(sizeof(TipoLista));
  lst->prim = lst->ult = NULL;
  return lst;
}

void inicializaListaAmigos(TipoLista *lista){
  tCelula *aux=lista->prim;
  while(aux != NULL){
    InicializaListaDePessoas(aux->pessoa->amigos);
    aux=aux->prox;
  }
}

void InserePessoa (Pessoa* pessoa, TipoLista* lista){
  tCelula* nova = (tCelula*)malloc(sizeof(tCelula));
  nova->pessoa = pessoa;
  nova->prox=NULL;
  if (lista->prim == NULL) {
    lista->prim = nova;
    lista->ult = nova;
  }
  else{
    lista->ult->prox = nova;
    lista->ult = nova;
  }
}
// void InsereAmigo (Pessoa* amigo, TipoLista* lista){
//   //mesma função da insere pessoa porem o ponteiro n precisa ser alocado pois apontara pra pessoa q ja existe na lista
//   tCelula* nova;
//   nova->pessoa=amigo;
//   if (lista->prim == NULL) {
//     lista->prim = nova;
//     lista->ult = nova;
//   }
//   else{
//     lista->ult->prox = nova;
//     lista->ult = nova;
//   }

// }

tCelula* retornaCelula(TipoLista* lista,char *nome){
  tCelula* aux = lista->prim;
  while (strcmp(nome,aux->pessoa->nome) != 0){
    aux = aux->prox;
  }
  return aux;
}

void AdicionaAmigo(TipoLista* lista, char* adicionador, char* adicionado){
  tCelula* aux;
  tCelula* aux2;
  if (lista != NULL) {
    aux = retornaCelula(lista,adicionador); //percorre a lista e acha a 1 pessoa
    aux2 =retornaCelula(lista,adicionado); //percorre a lista e acha a 2 pessoa
    InserePessoa(aux2->pessoa,aux->pessoa->amigos); //insere a pessoa 2 na lista de amigos da pessoa 1 e vice-versa
    InserePessoa(aux->pessoa,aux2->pessoa->amigos);
  }
}

void ImprimePessoa (Pessoa* p){
  puts(p->nome);
  //falta playlist
  printf("--Playlists--\n");
  ImprimePlaylists(p->playlists);
}

void ImprimeLista (TipoLista* lista){
  // Imprime Lista de Pessoas
  tCelula* aux = lista->prim;
  while (aux != NULL) {
    puts("\n");
    ImprimePessoa(aux->pessoa);
    puts("--Amigos--"); // Abaixo - Logica para impressao de amigos
    tCelula* aux2 = aux->pessoa->amigos->prim;
    while(aux2 != NULL){
      printf("%s\n", aux2->pessoa->nome);
      aux2 = aux2->prox;
    }
    aux=aux->prox;
  }
}



//Funcoes de retorno p/ escopo
Playlists* retornaPlaylists(TipoLista *lista,char *nome){
  tCelula *aux=retornaCelula(lista,nome);
  return aux->pessoa->playlists;
}

void adicionaMusicas(TipoLista *lista){
  tCelula *aux;
  aux=lista->prim;
  while(aux != NULL){
    leInfoPlaylists(aux->pessoa->playlists);
    aux=aux->prox;
  }
}

void refatoraPlaylists(TipoLista *lista){
  tCelula *aux;      
  aux=lista->prim;
  //teoricamente percorre as playlists de todas pessoas
  while(aux != NULL){    
    RefatoraPlaylistsDePessoa(aux->pessoa->playlists);
    RetiraPlayVazias(aux->pessoa->playlists);
    
    aux=aux->prox;
  }
}


//  Funcoes libera
TipoLista* LiberaListaPessoas(TipoLista* lista){
  // Libera Lista de Pessoas
}
//
TipoLista* LiberaPessoa(Pessoa* p){

}
