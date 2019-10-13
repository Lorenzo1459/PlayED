#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  TipoLista* pessoas = InicializaListaDePessoas();

  FILE *fp = fopen("amizade.txt","r");
  char c;
  char buffer[20],buffer2[2][20];
  int n = 0;

  if (fp != NULL){
      while ((c = fgetc(fp)) != '\n') {
        if (c != ';') {
          buffer[n] = c;
          n++;
        }
        else{
          InserePessoa(InicializaPessoa(buffer),pessoas);
          memset(buffer,0,strlen(buffer));
          n = 0;
        }
      }
      InserePessoa(InicializaPessoa(buffer),pessoas);
  }
  
  inicializaListaAmigos(pessoas);
  
  while((c=fgetc(fp))!= EOF ){
    n=0;
    while((c = fgetc(fp)) != ';'){
      buffer2[1][n] = c;
      n++;  
    }
    while ((c = fgetc(fp)) != '\n') {
      buffer2[2][n] = c;
      n++; 
    }
    AdicionaAmigo(pessoas,buffer2[1],buffer2[2]);

  }
  ImprimeLista(pessoas);

  
  fclose(fp);


   printf("Existem %d caracteres no arquivo.\n", n);

  return 0;
}
