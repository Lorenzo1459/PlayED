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
  p->amigos = InicializaListaDePessoas(); // inicializa lista vazia
  p->playlists = InicializaPlaylists(); // inicializa lista vazia
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
  if (lista->prim == NULL) { // quando a lista for fazia
    lista->prim = nova;
    lista->ult = nova;
  }
  else{
    lista->ult->prox = nova;
    lista->ult = nova;
  }
}

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

void ImprimePessoa (Pessoa* p){ // só pra teste
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
  // percorre as playlists de todas pessoas
  while(aux != NULL){
    RefatoraPlaylistsDePessoa(aux->pessoa->playlists);
    RetiraPlayVazias(aux->pessoa->playlists);

    aux=aux->prox;
  }
}

void PlayEDrefatorada(TipoLista* lista){
  FILE* fp5 = fopen("played-refatorada.txt", "w");
  tCelula* aux = lista->prim;
  while (aux != NULL) {
    Playlist* auxp = retornaPrimeiro(aux->pessoa->playlists);
    fprintf(fp5,"%s," ,aux->pessoa->nome);
    fprintf(fp5, "%d", num_playlists(aux->pessoa->playlists));
    while (auxp != NULL) {
      fprintf(fp5, ",%s.txt", retornaNome(auxp));
      auxp = retornaProximo(auxp);
    }
    fprintf(fp5, "\n");
    aux = aux->prox;
  }
fclose(fp5);
}

void cria_pasta(Pessoa* p){
  const int layer1 = 5;
    const int layer2 = 10;
    const int outfiles = 100;
    char buffer[100];    
    
    sprintf(buffer, "mkdir %s", p->nome);
    system(buffer);
}

void cria_pastas(TipoLista* l){
  tCelula* aux = l->prim;
  while(aux != NULL){
    cria_pasta(aux->pessoa);
    aux = aux->prox;
  }
}

void preenche_pasta(Pessoa* p){
  Playlist* aux = retornaPrimeiro(p->playlists);
  char buffer[40];  
  while(aux != NULL){ 
    sprintf(buffer,"%s/%s",p->nome,retornaNome(aux));
    FILE* fp6 = fopen(buffer,"w");
    TcelulaM* auxM = retornaPrimeiraCel(aux);
    while(auxM != NULL){
      fprintf(fp6,"%s\n",retornaNomeMusica(auxM));
      auxM = retornaProxCel(auxM);
    }    
    aux = retornaProximo(aux);
    fclose(fp6);
  }
}

void preenche_pastas(TipoLista* l){
  tCelula* aux = l->prim;
  while(aux != NULL){
    preenche_pasta(aux->pessoa);
    aux = aux->prox;
  }
}

void similaridades(TipoLista *lista){
  tCelula *pessoa=lista->prim;
  int quant=0;
  FILE *arq=fopen("similaridades.txt","w");
  while (pessoa !=NULL)
  {
    tCelula *pessoa2=pessoa->pessoa->amigos->prim;
    

    while(pessoa2 != NULL){
      quant=0;
      if(pessoa2!= pessoa){
        quant= ContaSimilaridade(pessoa->pessoa->playlists,pessoa2->pessoa->playlists);
        fprintf(arq,"\n%s;%s;%i\n",pessoa->pessoa->nome,pessoa2->pessoa->nome,quant);
      }
      pessoa2=pessoa2->prox;
    }
    pessoa=pessoa->prox;
  }
  fclose(arq);
}

int contaPessoas(TipoLista *pessoas){
  tCelula *aux=pessoas->prim;
  int cont=0;
  while(aux!= NULL){
    cont++;
    aux=aux->prox;
  }
return cont;
}
//  Funcoes libera
void LiberaListaPessoas(TipoLista* lista){
  tCelula *aux=lista->prim;
  tCelula *auxFree;
  
  while(aux != NULL){
    auxFree=aux;
    aux=aux->prox;

    LiberaPessoa(auxFree->pessoa);
    free(auxFree);
  }
}
//
void LiberaPessoa(Pessoa* p){
  Playlists *aux=p->playlists;
  tCelula *aux2=p->amigos->prim,*auxFree;
  free(p->nome);
  LiberaPlaylists(aux);
  free(aux);
  while(aux2!=NULL){
    auxFree=aux2;
    aux2=aux2->prox;
    free(auxFree);
  }
  free(p->amigos);
  free(p);
  


}
