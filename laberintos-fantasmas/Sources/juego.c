#include "../Headers/juego.h"
#include <windows.h>

int mostrarMenu()
{
    int opcion;

    puts("====== LABERINTOS Y FANTASMAS ======");
    puts("1) Jugar");
    puts("2) Ver ranking de jugadores");
    puts("3) Salir");

    scanf("%d", &opcion);
    getchar();

    return opcion;
}

void draw(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int i, j, k;
    int hayFantasma;
    tFantasma* fantasma;

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            if(i == jugador->posY && j == jugador->posX)
                printf("%c", jugador->j);
            else
            {
                hayFantasma = 0;
                for(k = 0 ; k < fantasmas->ce ; k++)
                {
                    fantasma = (tFantasma*)((char*)fantasmas->v + k * fantasmas->tamElem);

                    if((fantasma->posY == i && fantasma->posX == j) && fantasma->vivo == 1)
                    {
                        printf("F");
                        hayFantasma = 1;
                        break;
                    }
                }
                if(!hayFantasma)
                    printf("%c", laberinto->mat[i][j]);
            }
        }
        puts("");
    }
}


void procesarCelda(tJugador* jugador, tVector* fantasmas, char* celda)
{
    int i;
    tFantasma* fantasma;

    for(i = 0 ; i < fantasmas->ce ; i++)
    {
        fantasma = (tFantasma*)((char*)fantasmas->v + i * fantasmas->tamElem);
        if((jugador->posX == fantasma->posX && jugador->posY == fantasma->posY) && fantasma->vivo == 1)
        {
            jugador->vidas--;
            jugador->posX = jugador->posXIni;
            jugador->posY = jugador->posYIni;
            //liberarMovimientosFantasma(fantasma);
            fantasma->vivo = 0;
            //vectorEliminarPosicion(fantasmas, i);
        }
    }

    if (*celda == 'P')
    {
        jugador->puntos++;
        *celda = '.';
    }
    else if (*celda == 'V')
    {
        jugador->vidas++;
        *celda = '.';
    }
}

void inicializarJuego(tConfig* config, tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int xIni, yIni;

    inicializarConfiguracion(config);
    inicializarLaberinto(laberinto, &xIni, &yIni, config);
    inicializarJugador(jugador, xIni, yIni, config);
    vectorCrear(fantasmas, sizeof(tFantasma), config->maxNumeroFantasmas);

    cargarPosicionesFantasmas(fantasmas, laberinto);
    eliminarFantasmasLaberinto(laberinto);
}

void gameLoop(SOCKET sock, tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas, const char* nombreJugador)
{
    int nuevoX, nuevoY;
    char input;
    //char buffer[10];
    tFantasma* fantasma;
    int movimientos = 0;

    while(jugador->vidas > 0 && laberinto->mat[jugador->posY][jugador->posX] != 'S')
    {
        system("cls || clear");
        draw(laberinto, jugador, fantasmas);
        printf("Jugador: %s\n", nombreJugador); // Usar el parámetro
        printf("VIDAS: %d\nPUNTOS: %d\nMOVIMIENTOS: %d\n", jugador->vidas, jugador->puntos, movimientos);

        input = getch();

        calcularNuevaPosicion(jugador, input, &nuevoX, &nuevoY);

        if(esDirValida(laberinto, nuevoX, nuevoY))
        {
            registrarDireccion(jugador, input);
            mover(jugador, nuevoX, nuevoY);
            movimientos++;
        }

        for(int i = 0 ; i < fantasmas->ce ; i++)
        {
            fantasma = (tFantasma*)((char*)fantasmas->v + i * fantasmas->tamElem);
            if(fantasma->vivo == 1)
                moverFantasmas(fantasma, jugador, laberinto);
        }
        procesarCelda(jugador, fantasmas, &laberinto->mat[jugador->posY][jugador->posX]);
    }

    int ganada = (jugador->vidas > 0);
    //ganada

    //guardarPartida(nombreJugador, jugador->puntos, movimientos, ganada?'G':'P');
    if(sock != INVALID_SOCKET)
        enviarPartidaAlServidor(sock, nombreJugador, jugador->puntos, movimientos, ganada?'G':'P');
    system("cls || clear");
    if(jugador->vidas > 0)
    {
        puts("Has ganado!\n");
    }
    else
    {
        puts("Game Over\n");
    }


    mostrarAnimacion(laberinto, jugador, fantasmas);
    if(sock != INVALID_SOCKET)
        printf("Resumen de partida para %s:\n", nombreJugador);

    printf("Puntos: %d | Movimientos: %d | Resultado: %s\n", jugador->puntos, movimientos, ganada ? "Ganada" : "Perdida");

    /*printf("Lista de movimientos: ");
    while(!colaVacia(&jugador->colaMovimientos))
    {
        colaQuitar(&jugador->colaMovimientos, buffer, sizeof(buffer));
        printf("%s ", buffer);
    }
    mostrarMovimientosFantasma(fantasmas);*/
    puts("");
    system("pause");
    system("cls || clear");
    colaVaciar(&jugador->colaMovimientos);
    liberarMovimientosFantasmas(fantasmas);
}

void mostrarAnimacion(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int i;
    int j;
    int movJugadorXY[2] = {jugador->posXIni, jugador->posYIni};

    while(!colaVacia(&(jugador->colaMovimientos)))
    {
        //system("pause");

        laberinto->mat[movJugadorXY[1]][movJugadorXY[0]] = '.';
        colaQuitar(&(jugador->colaMovimientos), movJugadorXY, sizeof(movJugadorXY));
        laberinto->mat[movJugadorXY[1]][movJugadorXY[0]] = 'J';

        Sleep(300);
        system("cls || clear");
        for(i = 0 ; i < laberinto->cf ; i++)
        {
            for(j = 0 ; j < laberinto->cc ; j++)
            {
                printf("%c", laberinto->mat[i][j]);
            }
            puts("");
        }

    }

}
