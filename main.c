#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//#include "./Headers/common.h"
#include "./Headers/config.h"
#include "./Headers/jugador.h"
#include "./Headers/laberinto.h"
#include "./Headers/fantasma.h"
#include "./Headers/juego.h"
#include "./Headers/db.h"

#include "./Estructuras/Matriz.h"
#include "./Estructuras/Cola.h"

int main() {
    tConfig config;
    tLaberinto laberinto;
    tJugador jugador;
    tVector fantasmas;
    tArbol arbolUsuarios;
    char nombreJugador[51];
    int opcion;

    inicializarBD(&arbolUsuarios);

    opcion = mostrarMenu();
    while(opcion != 3)
    {
        if(opcion == 1)
        {
            printf("Ingrese su nombre: ");
            fgets(nombreJugador, sizeof(nombreJugador), stdin);
            guardarUsuario(&arbolUsuarios, nombreJugador);
            nombreJugador[strcspn(nombreJugador, "\n")] = 0;
            inicializarJuego(&config, &laberinto, &jugador, &fantasmas);
            gameLoop(&laberinto, &jugador, &fantasmas, nombreJugador);
        }
        if(opcion == 2)
        {
            mostrarRankingSimple();
        }

        opcion = mostrarMenu();
    }

    return 0;
}
