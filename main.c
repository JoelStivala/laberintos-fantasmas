#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "common.h"
#include "config.h"
#include "jugador.h"
#include "laberinto.h"
#include "fantasma.h"
#include "juego.h"

int main(int argc, char* argv[])
{
    tConfig config;
    tLaberinto laberinto;
    tJugador jugador;
    vFantasmas fantasmas;

    char input;
    int nuevoX, nuevoY;

    inicializarConfiguracion(&config);
    inicializarLaberinto(&laberinto, &config);
    inicializarJugador(&jugador, &config);
    inicializarFantasmas(&fantasmas, &config);

    cargarPosicionesFantasmas(&fantasmas, &laberinto);

    while(jugador.vidas > 0 && laberinto.mat[jugador.posY][jugador.posX] != 'S')
    {
        draw(&laberinto, &jugador, &fantasmas);
        printf("%d, %d\n", fantasmas.f[0].posX, fantasmas.f[0].posY);
        printf("%d, %d\n", fantasmas.f[1].posX, fantasmas.f[1].posY);
        printf("VIDAS: %d\nPUNTOS: %d\n", jugador.vidas, jugador.puntos);
        input = getch();

        calcularNuevaPosicion(&jugador, input, &nuevoX, &nuevoY);

        if(!hayBloque(&laberinto, nuevoX, nuevoY))
        {
            mover(&jugador, nuevoX, nuevoY);
            procesarCelda(&jugador, &laberinto.mat[jugador.posY][jugador.posX]);
        }
        for(int i = 0 ; i < config.maxNumeroFantasmas ; i++)
            moverFantasmas(&fantasmas.f[i], &jugador, &laberinto);
    }

    printf("GAME OVER\n");

    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    destruirFantasmas(&fantasmas);

    return 0;
}

