#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//#include "./Headers/common.h"
#include "./Estructuras/Matriz.h"
#include "./Headers/config.h"
#include "./Headers/jugador.h"
#include "./Headers/laberinto.h"
#include "./Headers/fantasma.h"
#include "./Headers/juego.h"

#include "./Estructuras/Cola.h"

int main(int argc, char* argv[])
{

    tConfig config;
    tLaberinto laberinto = {0};
    tJugador jugador;
    //vFantasmas fantasmas = {0};
    tVector vecFantasmas;

    int opcion;

    opcion = mostrarMenu();

    while(opcion != 3)
    {
        if(opcion == 1)
        {
            inicializarJuego(&config, &laberinto, &jugador, &vecFantasmas);
            gameLoop(&laberinto, &jugador, &vecFantasmas);
            destruirMatriz((void**)laberinto.mat, laberinto.cf);
            vectorDestruir(&vecFantasmas);
        }

        system("cls");
        opcion = mostrarMenu();
    }

    return 0;
}

