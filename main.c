#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "./Headers/common.h"
#include "./Headers/config.h"
#include "./Headers/jugador.h"
#include "./Headers/laberinto.h"
#include "./Headers/fantasma.h"
#include "./Headers/juego.h"


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
        }

        system("cls");
        opcion = mostrarMenu();
    }

    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    destruirFantasmas(&fantasmas);

    return 0;
}

