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

void InserePessoa (Pessoa* aluno, TipoLista* lista){
  tCelula* nova = (tCelula*)malloc(sizeof(tCelula));
  nova->pessoa = aluno;
  if (lista->prim == NULL) {
    lista->prim = nova;
    lista->ult = nova;
  }
  else{
    lista->ult->prox = nova;
    lista->ult = nova;
  }
}

void AdicionaAmigo(TipoLista* lista, Pessoa* adicionador, char* adicionado){
  tCelula* aux = lista->prim;
  while (aux != NULL) {
    if (strcmp(adicionado,lista->pessoa->nome) == 0) {
       // InserePessoa(aux,adicionador->amigos);
       
    }
    aux = aux->prox;
  }
}

void ImprimePessoa (Pessoa* p){
  // Imprime pessoa P
}

void ImprimeLista (TipoLista* lista){
  // Imprime Lista de Pessoas
}

TipoLista* Libera (TipoLista* lista){
  // Libera Lista de Pessoas
}
