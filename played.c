#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  TipoLista* pessoas = InicializaListaDePessoas();

  FILE *fp = fopen(argv[1],"r");
  char c;
  char buffer[20];
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
  while (c != '\n') {
    
  }
  fclose(fp);


  // printf("Existem %d caracteres no arquivo.\n", n);

  return 0;
}
