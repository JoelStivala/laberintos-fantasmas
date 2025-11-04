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

#define TAM_LINEA 255

#define LABERINTO_TXT "../../Files/laberinto.txt"

typedef struct
{
    char** mat;
    int cf;
    int cc;
} tLaberinto;

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config);
void dibujarLaberinto(tLaberinto* laberinto);
void eliminarFantasmasLaberinto(tLaberinto* laberinto);
int hayBloque(tLaberinto* laberinto, int posX, int posY);
int hayCamino(tLaberinto* laberinto, int posX, int posY);
int esDirValida(tLaberinto* laberinto, int posX, int posY);

#endif // LABERINTO_H_INCLUDED
