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

void draw(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas)
{
    int i, j, k;
    int hayFantasma;

    system("cls");

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            if(i == jugador->posY && j == jugador->posX)
                printf("%c", jugador->j);
            else
            {
                hayFantasma = 0;
                for(k = 0 ; k < fantasmas->cntFantasmas ; k++)
                {
                    if(fantasmas->f[k].posY == i && fantasmas->f[k].posX == j)
                    {
                        printf("%c", fantasmas->i);
                        hayFantasma = 1;
                        break; //reemplazar por un while luego
                    }
                }
                if(!hayFantasma)
                    printf("%c", laberinto->mat[i][j]);
            }

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
