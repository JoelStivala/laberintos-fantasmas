#include "laberinto.h"

int cargarLaberinto(FILE* pf, void* elem)
{
    char linea[255];
    tLaberinto* laberinto = elem;
    int i = 0;

    while(fgets(linea, 255, pf) && i < laberinto->cf)
    {
        sscanf(linea, "%s", laberinto->mat[i]);
        i++;
    }

    return TODO_OK;
}

int inicializarLaberinto(tLaberinto* laberinto, tConfig* config)
{
    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas);

    //TODO - Funcion para crear el archivo laberinto.txt, actualmente leemos el archivo directamente

    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;
    cargarRegistroMemoria("laberinto.txt", laberinto, cargarLaberinto);

    return TODO_OK;
}

int hayBloque(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '#';
}
