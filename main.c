#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "common.h"
#include "config.h"
#include "jugador.h"
#include "laberinto.h"
#include "juego.h"

int main(int argc, char* argv[])
{
    tConfig config;
    tLaberinto laberinto;
    tJugador jugador;

    char input;
    int nuevoX, nuevoY;

    inicializarConfiguracion(&config);
    inicializarLaberinto(&laberinto, &config);
    inicializarJugador(&jugador, &config);

    while(jugador.vidas > 0)
    {
        draw(&laberinto, &jugador);
        input = getch();

        calcularNuevaPosicion(&jugador, input, &nuevoX, &nuevoY);

        if(!hayBloque(&laberinto, nuevoX, nuevoY))
            mover(&jugador, nuevoX, nuevoY);
    }

    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    return 0;
}

