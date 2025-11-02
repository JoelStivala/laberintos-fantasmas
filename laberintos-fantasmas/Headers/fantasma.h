#ifndef FANTASMA_H_INCLUDED
#define FANTASMA_H_INCLUDED

#include "config.h"
#include "common.h"
#include "laberinto.h"
#include "jugador.h"
#include "../Estructuras/Vector.h"
#include "../Estructuras/Cola.h"

typedef struct
{
    int posX;
    int posY;
    tCola colaMovimientos;
    int vivo;
} tFantasma;

typedef struct
{
    tFantasma* f;
    int cntFantasmas;
    char i;
} vFantasmas;

void cargarPosicionesFantasmas(tVector* fantasmas, tLaberinto* laberinto);
void moverFantasmas(tFantasma* f, tJugador* j, tLaberinto* lab);
void liberarMovimientosFantasmas(tVector* fantasmas);
void mostrarMovimientosFantasma(tVector *fantasmas);

#endif // FANTASMA_H_INCLUDED
