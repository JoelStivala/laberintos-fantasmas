#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "config.h"
#include "jugador.h"

void inicializarMatriz(char** matriz, tJugador* jugador, int filas, int columnas);
void mostrarMatriz(char** matriz, int filas, int columnas);

int main(int argc, char* argv[])
{
    tConfig config;
    char** laberinto;
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

    laberinto = (char**)crearMatriz(sizeof(char), config.filas, config.columnas);

    inicializarMatriz(laberinto, &jugador, config.filas, config.columnas);
    mostrarMatriz(laberinto, config.filas, config.columnas);

    destruirMatriz((void**)laberinto, config.filas);
    return 0;
}

void inicializarMatriz(char** matriz, tJugador* jugador, int filas, int columnas)
{
    for(int i = 0 ; i < filas ; i++)
    {
        for(int j = 0 ; j < columnas ; j++)
        {
            matriz[i][j] = '.';
        }
    }
    matriz[jugador->posY][jugador->posX] = 'J';
}

void mostrarMatriz(char** matriz, int filas, int columnas)
{
    for(int i = 0 ; i < filas ; i++)
    {
        for(int j = 0 ; j < columnas ; j++)
        {
            printf("%c", matriz[i][j]);
        }
        puts("");
    }


}
