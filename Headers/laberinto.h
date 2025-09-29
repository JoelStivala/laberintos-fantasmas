#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>
#include "config.h"
#include "common.h"
#include "../Estructuras/Matriz.h"

typedef struct
{
    char** mat;
    int cf;
    int cc;
} tLaberinto;

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config);
void dibujarLaberinto(tLaberinto* laberinto);
int hayBloque(tLaberinto* laberinto, int posX, int posY);
void eliminarFantasmasLaberinto(tLaberinto* laberinto);

#endif // LABERINTO_H_INCLUDED
