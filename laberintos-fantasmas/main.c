#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//#include "./Headers/common.h"
#include "./Headers/config.h"
#include "./Headers/jugador.h"
#include "./Headers/laberinto.h"
#include "./Headers/fantasma.h"
#include "./Headers/juego.h"
//#include "./Headers/db.h"

#include "./Estructuras/Matriz.h"
#include "./Estructuras/Cola.h"

#include "cliente_lib.h"

int main()
{
    tConfig config;
    tLaberinto laberinto;
    tJugador jugador;
    tVector fantasmas;
    //tArbol arbolUsuarios;
    char nombreJugador[51];
    int opcion;

    if (init_winsock() != 0) {
        printf("Error al inicializar Winsock\n");
        //return 1;
    }

    printf("Conectado al servidor.\n");

    SOCKET sock = connect_to_server(SERVER_IP, PORT);
    if (sock == INVALID_SOCKET) {
        printf("No se pudo conectar al servidor\n");
        WSACleanup();
        //return 1;
    }

    //inicializarBD(&arbolUsuarios);

    opcion = mostrarMenu();
    while(opcion != 3)
    {
        system("cls || clear");
        if(opcion == 1)
        {
            if(sock != INVALID_SOCKET)
            {
                printf("Ingrese su nombre: ");
                fgets(nombreJugador, sizeof(nombreJugador), stdin);
                //guardarUsuario(&arbolUsuarios, nombreJugador);
                enviarUsuarioAlServidor(sock, nombreJugador);
                nombreJugador[strcspn(nombreJugador, "\n")] = 0;
            }

            inicializarJuego(&config, &laberinto, &jugador, &fantasmas);
            gameLoop(sock, &laberinto, &jugador, &fantasmas, nombreJugador);

        }
        if(opcion == 2)
        {
            if(sock != INVALID_SOCKET)
            {
                solicitarRankingAlServidor(sock);
            }
            else
            {
                printf("No se pudo conectar con la base de datos.\n");
            }
            system("pause");
            system("cls || clear");
        }

        opcion = mostrarMenu();
    }

    if(sock != INVALID_SOCKET)
        close_connection(sock);

    return 0;
}
