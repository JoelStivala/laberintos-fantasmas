#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "config.h"
#include "../Estructuras/Cola.h"
#include <string.h>

typedef struct
{
    int posX;
    int posY;
    int posXIni;
    int posYIni;
    int vidas;
    int puntos;
    tCola colaMovimientos;
    char j;
}tJugador;

void inicializarJugador(tJugador* jugador, int xIni, int yIni, tConfig* config);
void calcularNuevaPosicion(tJugador* jugador, char input, int* nuevoX, int* nuevoY);
void mover(tJugador* jugador, int nuevoX, int nuevoY);
void registrarDireccion(tJugador* jugador, char input);

#endif // JUGADOR_H_INCLUDED
