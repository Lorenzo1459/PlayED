#ifndef PESSOA_H
#define PESSOA_H

#include "playlist.h"

typedef struct pessoa Pessoa;

typedef struct tipolista TipoLista;

Pessoa* InicializaPessoa(char* nome);

TipoLista* InicializaListaDePessoas();

void InserePessoa (Pessoa* aluno, TipoLista* lista);

void AdicionaAmigo(TipoLista* lista, Pessoa* adicionador, char* adicionado);

// Pessoa* Retira (TipoLista* lista, ""fator de busca p/ retirar""); // Se for preciso retirar

void ImprimePessoa (Pessoa* p);

void ImprimeLista (TipoLista* lista);

TipoLista* Libera (TipoLista* lista);

#endif //PESSOA_H
