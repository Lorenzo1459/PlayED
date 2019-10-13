#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tcelula tCelula;

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
  Playlist* playlists; // Lista de playlists
};

Pessoa* InicializaPessoa(char* nome){
  Pessoa* p = (Pessoa*)malloc(sizeof(Pessoa));
  p->nome = strdup(nome);
  p->amigos = InicializaListaDePessoas();
  p->playlists = NULL;
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

void InserePessoa (Pessoa* amigo, TipoLista* lista){
  tCelula* nova = (tCelula*)malloc(sizeof(tCelula));
  nova->pessoa = amigo;
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

// void InsereAmigo(TipoLista *listaAmigos,tCelula *amigo){
//   //função recebe a lista de amigos e a celula do amigo a ser adicionado e adiciona ele na lista
//   tCelula* nova = (tCelula*)malloc(sizeof(tCelula));
//   nova->pessoa = amigo->pessoa;
//   nova->prox=NULL;
  
//   if (listaAmigos->prim == NULL) {
//     listaAmigos->prim = nova;
//     listaAmigos->ult = nova;
//   }
//   else{
//     listaAmigos->ult->prox = nova;
//     listaAmigos->ult = nova;
//   }

// }

void AdicionaAmigo(TipoLista* lista, char* adicionador, char* adicionado){
  tCelula* aux = lista->prim;
  tCelula* aux2 = lista->prim;
  while (aux != NULL) {
    while (strcmp(adicionador,aux->pessoa->nome) != 0) {
      //percorre a lista e acha a 1 pessoa
      aux = aux->prox;
    
    }
    
    while (strcmp(adicionado,aux2->pessoa->nome) != 0) {
    //percorre a lista e acha a 2 pessoa
      
    aux2 = aux2->prox;
    }
    //insere a pessoa 2 na lista de amigos da pessoa 1 e vice-versa
    InserePessoa(aux2->pessoa,aux->pessoa->amigos);
    InserePessoa(aux->pessoa,aux2->pessoa->amigos); 
  }
}

void ImprimePessoa (Pessoa* p){
  // Imprime pessoa P
}

void ImprimeLista (TipoLista* lista){
  // Imprime Lista de Pessoas
  tCelula* aux = lista->prim;
  while (aux != NULL) {
    puts(aux->pessoa->nome);
    puts("--amigos--");
    ImprimeLista(aux->pessoa->amigos);
    puts("--fim--");
    //falta a parte de imprimir a playlist pq ainda n foi implementada
  }
}

TipoLista* Libera (TipoLista* lista){
  // Libera Lista de Pessoas
}
