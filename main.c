#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "jugador.h"
#include "laberinto.h"


int main(int argc, char* argv[])
{
    tConfig config;
    tLaberinto laberinto;
    tJugador jugador;

    jugador.posX = 3;
    jugador.posY = 5;

    cargarRegistroMemoria("config.txt", &config, cargarConfiguracion);

    printf("%d\n", config.filas);
    printf("%d\n", config.columnas);
    printf("%d\n", config.vidasInicio);
    printf("%d\n", config.maxNumeroFantasmas);
    printf("%d\n", config.maxNumeroPremios);
    printf("%d\n", config.maxVidasExtra);

    laberinto.mat = (char**)crearMatriz(sizeof(char), config.filas, config.columnas);

    inicializarLaberinto(&laberinto, config.filas, config.columnas);
    dibujarLaberinto(&laberinto);

    destruirMatriz((void**)laberinto.mat, laberinto.cf);
    return 0;
}

