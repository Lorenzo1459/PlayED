#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(/*int argc, char const *argv[]*/) {

  TipoLista* pessoas = InicializaListaDePessoas();

  FILE *fp = fopen("amizade.txt","r");
  char c;
  char buffer[20], buffer2[2][20];;
  int n = 0;

  if (fp != NULL){
    while ((c = fgetc(fp)) != '\n') {
      if (c != ';') {
        buffer[n] = c;
        n++;
      }
      
      else{
        buffer[n]='\0';
        InserePessoa(InicializaPessoa(buffer),pessoas);
        memset(buffer,0,strlen(buffer));
        n = 0;
      }
    }
    InserePessoa(InicializaPessoa(buffer),pessoas);
    memset(buffer,0,strlen(buffer));
    
  
  
    inicializaListaAmigos(pessoas);

    while((c=fgetc(fp))!= EOF ){
      n=0;
      //le o nome do primeira pessoa
      do{
        buffer2[0][n] = c;
        n++; 
        
      }while((c = fgetc(fp)) != ';');
      buffer2[0][n]='\0';

      //fgetc pra pular o ponto e virgula
      c=fgetc(fp);
      n=0;
      //le o nome da 2 pessoa
      do{
        buffer2[1][n] = c;
        
        n++;  
      }
      while ((c = fgetc(fp)) != '\n');
      buffer2[1][n]='\0';

      AdicionaAmigo(pessoas,buffer2[0],buffer2[1]);
      memset(buffer2[0],0,strlen(buffer2[0]));
      memset(buffer2[1],0,strlen(buffer2[1]));
      
      
    }
  }

  ImprimeLista(pessoas);

  
  fclose(fp);

  //ler o playlists.txt
  fp=fopen("playlists.txt","r");
  if (fp != NULL){
    int quantPlaylists=0;
    char *aux[20];
    
    n=0;
    while(c=fgetc(fp)!= EOF){
      //le o nome da pessoa
      do{
        buffer2[1][n] = c;
        n++;
      }while((c = fgetc(fp)) != ';');
      buffer2[1][n]='\0';

      //le o numero de playlists;
      c=fgetc(fp);
      quantPlaylists=(int)(c=fgetc(fp));
      c=fgetc(fp);
      for(int i=0;i<quantPlaylists;i++){
        while(c=fgetc(fp)!=';'){
          buffer[n] = c;
          n++;
          
        }
        buffer[n]='\0';
        CriaPlaylist(pessoas,buffer[1],buffer);
      }
    }
  }


  return 0;
}
