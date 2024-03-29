#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct playlists Playlists;
typedef struct playlist Playlist;
typedef struct tcelulam TcelulaM;

typedef struct musica Musica;

Playlists* InicializaPlaylists();
Playlist* InicializaPlaylist(char *nome);
Musica* InicializaMusica(char* artista, char* nome);

void LeArqMusicas(char *nomePlaylist,Playlist *playlist);
void leInfoPlaylists(Playlists *playlists);
void RefatoraPlaylistsDePessoa(Playlists *playlists);
Playlists* RefatoraUmaPlaylist(Playlist* p);
TcelulaM* retiraMusica(Musica *musica,Playlist* playlist);

void InsereMusica (Musica* mus, Playlist* lista);

void ImprimePlaylist (Playlist* p);
void ImprimePlaylists (Playlists* p);

void InserePlaylist(Playlists *playlists,char *nomePlaylist); //insere pelo nome (inicializando)
void InserePlaylist2(Playlists *playlists,Playlist* p); // insere dada playlist em uma lista de playlists
Playlists* UnePlaylists(Playlists *playlists,Playlists* playlists2); // Une duas listas de playlists

void RetiraPlayVazias(Playlists *playlists);
Musica* SeparaCelulaM(TcelulaM *celula);
void TranfereMusica(TcelulaM *celula,Playlist *lista);

static int PlaylistJaExistente(char* nome, Playlists* p);
void LocalizaPlaylistEInsere(char* nome, Playlists* p);
//funcoes de retorno p/ escopo caso necessarias
Playlist* retornaPrimeiro(Playlists* p);
Playlist* retornaProximo(Playlist* p);
int ContaSimilaridade(Playlists *pessoa,Playlists*pessoa2);

int num_playlists(Playlists* p);

char* retornaNome(Playlist* p);

TcelulaM* retornaPrimeiraCel(Playlist* p);
TcelulaM* retornaProxCel(TcelulaM* p);
char* retornaNomeMusica(TcelulaM* cel);
void LiberaPlaylists(Playlists* p);

#endif //PLAYLIST_H_
