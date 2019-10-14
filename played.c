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
  char buffer[32], buffer2[2][32];;
  int n = 0;

  if (fp != NULL){
    while ((c = fgetc(fp)) != '\n') {
      if (c == ' ')
      {
        continue;
      }
      
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
      }while ((c = fgetc(fp)) != '\n');
      buffer2[1][n]='\0';
      AdicionaAmigo(pessoas,buffer2[0],buffer2[1]);
      memset(buffer2[0],0,strlen(buffer2[0]));
      memset(buffer2[1],0,strlen(buffer2[1]));
      
      
    }
  }

  ImprimeLista(pessoas);

  
  fclose(fp);

  //ler o playlists.txt
  
  if (fp2 != NULL){
    int quantPlaylists=0;        
    //trocar i por quant de pessoas
    for (int i = 0; i < 4; i++)
    {
     n=0;
    while((c=fgetc(fp2))!= ';'){
  
      if (c == ' ')
      {
        continue;
      }

      
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
      //printf("aaaaaaaaaaaaaaaaaaaaaa %c",c);
      if (c != ';')
      {
        buffer2[1][n] = c;
        n++;
      }
      else if (c == ';' || c == '\n'){        
        
        buffer2[1][n]='\0';
        // puts(buffer2[1]);        
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
    
    
    // puts(buffer);
      

      //le o nome da pessoa    
      // printf("A %c", c);
      // do{
      //   printf("B %c", c);
      //   buffer2[1][n] = c;
      //   n++;

      // }while(c  != ';');
      // printf("C %c", c);
      // buffer2[1][n]='\0';      
      // //le o numero de playlists;
      // c=fgetc(fp2);
      // fscanf(fp2,"%i",&quantPlaylists);
      // c=fgetc(fp2);
      // for(int i=0;i<quantPlaylists;i++){
      //   while(c=fgetc(fp2)!=';'){
      //     buffer[n] = c;
      //     n++;
          
      //   }
      //   buffer[n]='\0'; 


        
               
        //puts(buffer);
        //CriaPlaylist(retornaPlaylists(pessoas,buffer2[1]),buffer);
      // }    
  }


  return 0;
}