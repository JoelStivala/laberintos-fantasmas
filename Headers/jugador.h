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
void calcularNuevaPosicion(tJugador* jugador, char input, int* nuevoX, int* nuevoY);
void mover(tJugador* jugador, int nuevoX, int nuevoY);

#endif // JUGADOR_H_INCLUDED
