#include "../Headers/jugador.h"

void inicializarJugador(tJugador* jugador, int xIni, int yIni, tConfig* config)
{
    int movXY[2] = {xIni, yIni};

    jugador->posX = xIni;
    jugador->posY = yIni;
    jugador->posXIni = xIni;
    jugador->posYIni = yIni;
    jugador->puntos = 0;
    jugador->vidas = config->vidasInicio;
    colaCrear(&(jugador->colaMovimientos));
    colaEncolar(&jugador->colaMovimientos, movXY, sizeof(movXY));
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

void registrarDireccion(tJugador* jugador, char input)
{
    int movXY[2] = {jugador->posX, jugador->posY}; //arriba, abajo, izquierda, derecha
    if(input == 'a')
        movXY[0]--;
    else if(input == 'd')
        movXY[0]++;
    else if(input == 'w')
        movXY[1]--;
    else if(input == 's')
        movXY[1]++;

    colaEncolar(&jugador->colaMovimientos, movXY, sizeof(movXY));
}
