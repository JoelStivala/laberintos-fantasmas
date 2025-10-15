#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include "config.h"
#include "common.h"
#include "../Estructuras/Matriz.h"

#define PARED '#'
#define CAMINO '.'
#define ENTRADA 'E'
#define SALIDA 'S'

typedef struct
{
    char** mat;
    int cf;
    int cc;
} tLaberinto;

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config);
void dibujarLaberinto(tLaberinto* laberinto);
int hayBloque(tLaberinto* laberinto, int posX, int posY);
int hayCamino(tLaberinto* laberinto, int posX, int posY);
void eliminarFantasmasLaberinto(tLaberinto* laberinto);

void acondicionarLaberinto(char** mat, int filas, int columnas);
int generarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni);
void algoritmoGenerador(char** mLaberinto, int x, int y, int filas, int columnas, int* ultimoX, int* ultimoY,
                        int dx[], int dy[], int dir[]);
int esDirValida(char** mLaberinto, int x, int y, int filas, int columnas);
void posicionarElementos(tLaberinto* laberinto, tConfig* config);
void aleatoriezarAparicionDeElem(tLaberinto* laberinto, int* x, int* y);
void facilitarLaberinto(tLaberinto* laberinto);
#endif // LABERINTO_H_INCLUDED
