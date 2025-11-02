#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include "config.h"
#include "common.h"
#include "../Estructuras/Matriz.h"

#define BLOQUE '#'
#define CAMINO '.'
#define ENTRADA 'E'
#define SALIDA 'S'

#define TRUE 1
#define FALSE 0

typedef struct
{
    char** mat;
    int cf;
    int cc;
} tLaberinto;

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config);
void dibujarLaberinto(tLaberinto* laberinto);
void eliminarFantasmasLaberinto(tLaberinto* laberinto);

void acondicionarLaberinto(char** mat, int filas, int columnas);
int generarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni);
void algoritmoGenerador(tLaberinto* laberinto, int x, int y,
                        const int dx[], const int dy[], int dir[]);
void posicionarElementos(tLaberinto* laberinto, tConfig* config);
void aleatoriezarAparicionDeElem(tLaberinto* laberinto, int* x, int* y);
void facilitarLaberinto(tLaberinto* laberinto);

int hayBloque(tLaberinto* laberinto, int posX, int posY);
int hayCamino(tLaberinto* laberinto, int posX, int posY);
int esDirGenLabValida(tLaberinto* laberinto, int posX, int posY);
int esDirValida(tLaberinto* laberinto, int posX, int posY);
#endif // LABERINTO_H_INCLUDED
