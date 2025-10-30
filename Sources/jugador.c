#include "../Headers/jugador.h"

void inicializarJugador(tJugador* jugador, int xIni, int yIni, tConfig* config)
{
    jugador->posX = xIni;
    jugador->posY = yIni;
    jugador->posXIni = xIni;
    jugador->posYIni = yIni;
    jugador->puntos = 0;
    jugador->vidas = config->vidasInicio;
    colaCrear(&(jugador->colaMovimientos));
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
    char direccion[10]; //arriba, abajo, izquierda, derecha
    if(input == 'a')
        strcpy(direccion, "izquierda");
    else if(input == 'd')
        strcpy(direccion, "derecha");
    else if(input == 'w')
        strcpy(direccion, "arriba");
    else if(input == 's')
        strcpy(direccion, "abajo");

    colaEncolar(&jugador->colaMovimientos, direccion, (strlen(direccion)+1));
}
