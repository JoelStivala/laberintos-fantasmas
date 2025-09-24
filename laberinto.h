#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <stdio.h>

typedef struct
{
    char** mat;
    int cf;
    int cc;
} tLaberinto;

void inicializarLaberinto(tLaberinto* laberinto, int cf, int cc);
void dibujarLaberinto(tLaberinto* laberinto);

#endif // LABERINTO_H_INCLUDED
