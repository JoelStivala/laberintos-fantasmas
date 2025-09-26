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
        printf("VIDAS: %d\nPUNTOS: %d\n", jugador.vidas, jugador.puntos);
        input = getch();

        calcularNuevaPosicion(&jugador, input, &nuevoX, &nuevoY);

        if(!hayBloque(&laberinto, nuevoX, nuevoY))
        {
            mover(&jugador, nuevoX, nuevoY);
            procesarCelda(&jugador, &laberinto.mat[jugador.posY][jugador.posX]);
        }
    }

    printf("GAME OVER\n");

    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    return 0;
}

