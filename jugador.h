#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "config.h"

typedef struct
{
    int posX;
    int posY;
    int vidas;
    int puntos;
    char j;
}tJugador;

void inicializarJugador(tJugador* jugador, tConfig* config);
void movimiento(tJugador* jugador, char input);

#endif // JUGADOR_H_INCLUDED
