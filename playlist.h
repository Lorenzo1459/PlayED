#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct playlists Playlists;
typedef struct playlist Playlist;
typedef struct tcelulam TcelulaM;

typedef struct musica Musica;

Playlist* InicializaPlaylist();

void InsereMusica (Musica* mus, Playlist* lista);

void ImprimePlaylist (Playlist* p);

Musica* InicializaMusica(char* nome);

// Musica* retornaMusica(Playlist* p); //Pensar em funçoes de retorno necessarias para fora do encapsulamento

#endif //PLAYLIST_H_
