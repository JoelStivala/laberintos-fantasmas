#include "jugador.h"

void inicializarJugador(tJugador* jugador, tConfig* config)
{
    jugador->posX = 0;
    jugador->posY = 0;
    jugador->puntos = 0;
    jugador->vidas = config->vidasInicio;
    jugador->j = 'J';
}

void movimiento(tJugador* jugador, char input)
{
    switch(input)
    {
        case('a'): jugador->posX--; break;
        case('d'): jugador->posX++; break;
        case('w'): jugador->posY--; break;
        case('s'): jugador->posY++; break;
    }
}
