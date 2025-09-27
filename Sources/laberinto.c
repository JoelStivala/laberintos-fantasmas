#include "../Headers/laberinto.h"

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

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config)
{
    int j = 1;
    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas);

    //TODO - Funcion para crear el archivo laberinto.txt, actualmente leemos el archivo directamente

    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;
    cargarRegistroMemoria("./Files/laberinto.txt", laberinto, cargarLaberinto);

    while(laberinto->mat[0][j] != 'E')
    {
        j++;
    }

    *xIni = j;
    *yIni = 1;

    return TODO_OK;
}

int hayBloque(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '#';
}

// Remplazar los fantasmas estaticos por '.'
void eliminarFantasmasLaberinto(tLaberinto* laberinto)
{
    int i, j;

    for(i = 1 ; i < laberinto->cf - 1 ; i++)
    {
        for(j = 1 ; j < laberinto->cc - 1 ; j++)
        {
            if(laberinto->mat[i][j] == 'F')
            {
                laberinto->mat[i][j] = '.';
            }
        }
    }
}
