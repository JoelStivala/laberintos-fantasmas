#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "common.h"
#include "config.h"
#include "jugador.h"
#include "laberinto.h"
#include "fantasma.h"
#include "juego.h"

void auxiliar(vFantasmas* fantasmas)
{
    for(int i = 0 ; i < fantasmas->cntFantasmas ; i++)
    {
        printf("%d %d\n", fantasmas->f[i].posX, fantasmas->f[i].posY);
    }
}

int main(int argc, char* argv[])
{
    tConfig config;
    tLaberinto laberinto = {0};
    tJugador jugador;
    vFantasmas fantasmas = {0};

    int opcion;

    opcion = mostrarMenu();

    while(opcion != 3)
    {
        if(opcion == 1)
        {
            inicializarJuego(&config, &laberinto, &jugador, &fantasmas);
            gameLoop(&laberinto, &jugador, &fantasmas);
            clearScreen();
        }

        system("cls");
        opcion = mostrarMenu();
    }


    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    destruirFantasmas(&fantasmas);

    return 0;
}

