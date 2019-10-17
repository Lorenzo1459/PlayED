#include "pessoa.h"
#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(/*int argc, char const *argv[]*/) {

  TipoLista* pessoas = InicializaListaDePessoas();

  FILE *fp = fopen("amizade.txt","r");
  FILE *fp2 = fopen("playlists.txt","r");
  char c;
  char buffer[32], buffer2[2][32];
  int n = 0;

  if (fp != NULL){
    while ((c = fgetc(fp)) != '\n') {
      if (c == ' ')
        continue;//Caso ache um espaço, avança o ponteiro do arquivo para o prox caractere
      if (c != ';') {
        buffer[n] = c; // Acrescenta cada caractere ao buffer, se diferente de ';'
        n++;
      }
      else{ //quando acha o ';' cria pessoa com o nome armazenado no buffer
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
      do{
        buffer2[0][n] = c; //le o nome do primeira pessoa e armazena em buffer2[0]
        n++;
      }
      while((c = fgetc(fp)) != ';');

      buffer2[0][n]='\0';
      c=fgetc(fp); //fgetc pra pular o ponto e virgula
      n=0;
      do{
        buffer2[1][n] = c; //le o nome da 2 pessoa e armazena em buffer2[1]
        n++;
      }
      while ((c = fgetc(fp)) != '\n');
      buffer2[1][n]='\0';

      AdicionaAmigo(pessoas,buffer2[0],buffer2[1]);// <<< EXPLICA AE ICARO
      memset(buffer2[0],0,strlen(buffer2[0])); //explicar o uso
      memset(buffer2[1],0,strlen(buffer2[1])); // de memset
    }
  }
  fclose(fp); // Fecha arquivo amizades



  //ler o playlists.txt

  if (fp2 != NULL){
    int quantPlaylists=0;
// ----------TROCAR I POR QUANT PESSOAS -- IMPORTANTE!!!!---------------------------------------------
    for (int i = 0; i < 4; i++){
     n=0;
    while((c=fgetc(fp2))!= ';'){
      if (c == ' ')
        continue;
      buffer2[0][n] = c;
      n++;
    }
    buffer2[0][n]='\0';
    fgetc(fp2);
    fscanf(fp2,"%i",&quantPlaylists);
    fgetc(fp2);
    n = 0;
    while ((c = fgetc(fp2)) != '\n')
    {
      if (c != ';'){
        buffer2[1][n] = c;
        n++;
      }
      else if (c == ';' || c == '\n'){
        buffer2[1][n]='\0';
        CriaPlaylist(retornaPlaylists(pessoas,buffer2[0]),buffer2[1]);
        memset(buffer2[1],0,strlen(buffer2[1]));
        n=0;
      }
    }
    CriaPlaylist(retornaPlaylists(pessoas,buffer2[0]),buffer2[1]);
    memset(buffer2[1],0,strlen(buffer2[1]));
    memset(buffer2[0],0,strlen(buffer2[0]));
    printf("%c",c);
    }
  }
  ImprimeLista(pessoas);

  return 0;
}
