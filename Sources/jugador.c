#include "../Headers/jugador.h"

void inicializarJugador(tJugador* jugador, tConfig* config)
{
    jugador->posX = 3;
    jugador->posY = 1;
    jugador->puntos = 0;
    jugador->vidas = config->vidasInicio;
    jugador->j = 'J';
}

void calcularNuevaPosicion(tJugador* jugador, char input, int* nuevoX, int* nuevoY)
{
    *nuevoX = jugador->posX;
    *nuevoY = jugador->posY;

    switch(input)
    {
        case('a'): (*nuevoX)--; break;
        case('d'): (*nuevoX)++; break;
        case('w'): (*nuevoY)--; break;
        case('s'): (*nuevoY)++; break;
    }
}

void mover(tJugador* jugador, int nuevoX, int nuevoY)
{
    jugador->posX = nuevoX;
    jugador->posY = nuevoY;
}
