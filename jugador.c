#include "jugador.h"

void movimiento(tJugador* jugador, char input)
{
    switch(input)
    {
        case('a'):
            jugador->posX--;
            break;
        case('d'):
            jugador->posX++;
            break;
        case('w'):
            jugador->posY--;
            break;
        case('s'):
            jugador->posY++;
            break;
    }
}
