#include "juego.h"

int mostrarMenu()
{
    int opcion;

    puts("======LABERINTOS Y FANTASMAS======");
    puts("1) Jugar");
    puts("2) Ver tabla de puntuaciones");
    puts("3) Salir");

    scanf("%d", &opcion);

    return opcion;
}

void draw(tLaberinto* laberinto, tJugador* jugador)
{
    int i;
    int j;

    system("cls");

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            if(i == jugador->posY && j == jugador->posX)
                printf("%c", jugador->j);
            else
                printf("%c", laberinto->mat[i][j]);
        }
        puts("");
    }
}

void procesarCelda(tJugador* jugador, char* celda)
{
    if (*celda == 'F')
    {
        jugador->vidas--;
        *celda = '.';
    }
    else if (*celda == 'P')
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
