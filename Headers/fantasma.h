#ifndef FANTASMA_H_INCLUDED
#define FANTASMA_H_INCLUDED

#include "config.h"
#include "common.h"
#include "laberinto.h"
#include "jugador.h"
typedef struct
{
    int posX;
    int posY;
} tFantasma;

typedef struct
{
    tFantasma* f;
    int cntFantasmas;
    char i;
} vFantasmas;

int inicializarFantasmas(vFantasmas* fantasmas, tConfig* config);
void cargarPosicionesFantasmas(vFantasmas* fantasmas, tLaberinto* laberinto);
void moverFantasmas(tFantasma* f, tJugador* j, tLaberinto* lab);
void eliminarFantasmasPosicion(vFantasmas* fantasmas, int pos);
void destruirFantasmas(vFantasmas* fantasmas);
#endif // FANTASMA_H_INCLUDED
