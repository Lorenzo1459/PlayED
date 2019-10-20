#ifndef PESSOA_H
#define PESSOA_H

#include "playlist.h"

typedef struct pessoa Pessoa;
typedef struct tcelula tCelula;

typedef struct tipolista TipoLista;

Pessoa* InicializaPessoa(char* nome);

TipoLista* InicializaListaDePessoas();

void inicializaListaAmigos(TipoLista *lista);

void InserePessoa (Pessoa* aluno, TipoLista* lista);

void InsereAmigo (Pessoa* amigo, TipoLista* lista);

tCelula* retornaCelula(TipoLista* lista,char *nome);

void AdicionaAmigo(TipoLista* lista, char* adicionador, char* adicionado);

void adicionaMusicas(TipoLista *lista);

void refatoraPlaylists(TipoLista *lista);
// Pessoa* Retira (TipoLista* lista, ""fator de busca p/ retirar""); // Se for preciso retirar

void ImprimePessoa (Pessoa* p);

void ImprimeLista (TipoLista* lista);

TipoLista* LiberaListaPessoas(TipoLista* lista);

void inicializaListaAmigos(TipoLista *lista);

Playlists* retornaPlaylists(TipoLista *lista,char *nome);
void adicionaMusicas(TipoLista *lista);

#endif //PESSOA_H
