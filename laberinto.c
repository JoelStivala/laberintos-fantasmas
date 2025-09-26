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

    fclose(pf);

    return TODO_OK;
}


int inicializarLaberinto(tLaberinto* laberinto, tConfig* config, const char* nombreLaberinto)
{
    int i;
    int j;

    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas);

    if(!laberinto->mat)
    {
        return ERR_MEMORIA;
    }


    //TODO - Funcion para crear el archivo laberinto.txt

    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;

    cargarRegistroMemoria(nombreLaberinto, laberinto, cargarLaberinto);

    return TODO_OK;
}
