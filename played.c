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
    //faz a mesma coisa do else anterior pra ultima linha visto que não existe '\n'
    buffer[n]='\0';
    InserePessoa(InicializaPessoa(buffer),pessoas);
    memset(buffer,0,strlen(buffer));

    //inicializaListaAmigos(pessoas);


    while((c=fgetc(fp))!= EOF ){ //faz a adição dos amigos
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
        buffer2[1][n] = c; // le o nome da 2 pessoa e armazena em buffer2[1]
        n++;
      }
      while ((c = fgetc(fp)) != '\n');
      buffer2[1][n]='\0';

      AdicionaAmigo(pessoas,buffer2[0],buffer2[1]);
      memset(buffer2[0],0,strlen(buffer2[0])); // memset reseta os buffers pra não guardar lixo no proximo uso
      memset(buffer2[1],0,strlen(buffer2[1])); 
    }
  }
  fclose(fp); // Fecha arquivo amizades



  //ler o playlists.txt

  if (fp2 != NULL){
    int quantPlaylists=0,quantPessoas=0;
    quantPessoas=contaPessoas(pessoas);

    for (int i = 0; i < quantPessoas; i++){

     n=0;
    while((c=fgetc(fp2))!= ';'){ // le o nome da pessoa
      if (c == ' ')
        continue;
      buffer2[0][n] = c;
      n++;
    }
    buffer2[0][n]='\0';
    fgetc(fp2);//pula o ;
    fscanf(fp2,"%i",&quantPlaylists); //le a quant de playlists
    fgetc(fp2);//pula o outro ;
    n = 0;
    while ((c = fgetc(fp2)) != '\n')
    {
      if (c != ';'){ // le o nome do arquivo da playlist
        buffer2[1][n] = c;
        n++;
      }
      else if (c == ';' || c == '\n'){ // quando acha o ; chama a função pra criar as playlists com seus respectivos nomes
        buffer2[1][n]='\0';
        InserePlaylist(retornaPlaylists(pessoas,buffer2[0]),buffer2[1]);
        memset(buffer2[1],0,strlen(buffer2[1]));
        n=0;
      }
    }

    InserePlaylist(retornaPlaylists(pessoas,buffer2[0]),buffer2[1]); // chama a função mais uma vez pra ultima linha e reseta os buffers
    memset(buffer2[1],0,strlen(buffer2[1]));
    memset(buffer2[0],0,strlen(buffer2[0]));
    printf("%c",c);
    }
  }
  
  fclose(fp2);
  adicionaMusicas(pessoas); // adiciona as musicas as suas respectivas playlists
  printf("Musicas adicionadas...\n");
  
  refatoraPlaylists(pessoas); // refatora as playlists
  printf("Playlists Refatoradas...\n");

  
  PlayEDrefatorada(pessoas); // cria os arquivos de saida
  printf("Arquivo played-refatorada.txt gerado...\n");
  cria_pastas(pessoas);
  printf("Diretórios criados...\n");
  preenche_pastas(pessoas);
  printf("Pastas preenchidas...\n");
  printf("Concluído.\n");

  similaridades(pessoas);
  LiberaListaPessoas(pessoas);
  free(pessoas);
  //ImprimeLista(pessoas);

  return 0;
}
