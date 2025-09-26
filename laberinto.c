#include "laberinto.h"

int inicializarLaberinto(tLaberinto* laberinto, tConfig* config)
{
    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas);

    if(!laberinto->mat)
    {
        return ERR_MEMORIA;
    }

    int i;
    int j;

    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            laberinto->mat[i][j] = '.';
        }
    }

    return TODO_OK;
}
