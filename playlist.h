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
void RefatoraDeVerdade(Playlists *playlists);
void RefatoraPorNome(Musica *musica,Playlists *playlists,Playlist *playAtual);
Musica* retiraMusica(Musica *musica,Playlist* playlist);

void InsereMusica (Musica* mus, Playlist* lista);

void ImprimePlaylist (Playlist* p);
void ImprimePlaylists (Playlists* p);

void CriaPlaylist(Playlists *playlists,char *nomePlaylist);



//funcoes de retorno p/ escopo caso necessarias
// Playlist* retornaPrimeiro(Playlists* p);
// Playlist* retornaProximo(Playlist* p);

#endif //PLAYLIST_H_
