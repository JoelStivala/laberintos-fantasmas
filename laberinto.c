#include "laberinto.h"

void inicializarLaberinto(tLaberinto* laberinto, int cf, int cc)
{
    int i;
    int j;
    laberinto->cf = cf;
    laberinto->cc = cc;
    for(i = 0 ; i < cf ; i++)
    {
        for(j = 0 ; j < cc ; j++)
        {
            laberinto->mat[i][j] = '.';
        }
    }
}

void dibujarLaberinto(tLaberinto* laberinto)
{
    int i;
    int j;
    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            printf("%c", laberinto->mat[i][j]);
        }
        puts("");
    }
}
