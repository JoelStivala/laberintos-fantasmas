#include "../Headers/laberinto.h"

#define MAX(a,b) ((a)>(b)?(a):(b))

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

/*
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
*/

int hayBloque(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '#';
}

int hayCamino(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '.';
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

void acondicionarLaberinto(char** mat, int filas, int columnas)
{
    int i, j;

    for(i = 0; i < filas; i ++)
        for(j = 0; j < columnas; j ++)
            mat[i][j] = PARED;
}

///NUEVA
int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config)
{
    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas); //validar la creacion
    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;

    acondicionarLaberinto(laberinto->mat, laberinto->cf, laberinto->cc);

    //Necesario para la aleatoriedad
    srand(time(NULL));

    generarLaberinto(laberinto, xIni, yIni);

    facilitarLaberinto(laberinto);

    posicionarElementos(laberinto, config);

    return TODO_OK;
}

void facilitarLaberinto(tLaberinto* laberinto)
{
    int auxX, auxY;
    int cont = MAX(laberinto->cc / 2, laberinto->cf / 2);

    while(cont > 0) //Crea x pasillos según cont
    {
        do
        {
            auxX = 1 + rand() % (laberinto->cc - 3); //+1 para asegurar que no sea borde
            auxY = 1 + rand() % (laberinto->cf - 3); //-3 para asegurar que no sea borde
        }while(!hayBloque(laberinto, auxX, auxY));

        laberinto->mat[auxY][auxX] = '.';
        cont--;
    }

}

void posicionarElementos(tLaberinto* laberinto, tConfig* config)
{
    int x, y;
    int cantElem;

    //Fantasmas
    cantElem = config->maxNumeroFantasmas;
    while(cantElem > 0)
    {
        aleatoriezarAparicionDeElem(laberinto, &x, &y);

        laberinto->mat[y][x] = 'F';
        cantElem --;
    }

    //Premios
    cantElem = config->maxNumeroPremios;
    while(cantElem > 0)
    {
        aleatoriezarAparicionDeElem(laberinto, &x, &y);

        laberinto->mat[y][x] = 'P';
        cantElem --;
    }

    //Vidas Extra
    cantElem = config->maxVidasExtra;
    while(cantElem > 0)
    {
        aleatoriezarAparicionDeElem(laberinto, &x, &y);

        laberinto->mat[y][x] = 'V';
        cantElem --;
    }
}

//Puede fallar?
void aleatoriezarAparicionDeElem(tLaberinto* laberinto, int* x, int* y)
{
    int auxX, auxY;

    do
    {
        auxX = rand() % (laberinto->cc - 1);
        auxY = rand() % (laberinto->cf - 1);
    }while(!hayCamino(laberinto, auxX, auxY));

    *x = auxX;
    *y =  auxY;
}

int generarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni)
{
    int ultimoX, ultimoY;
    // izquierda, derecha, arriba, abajo
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int dir[] = {0, 1, 2, 3};

    //Generar entrada al azar
    *yIni = 0;
    *xIni = rand() % laberinto->cc;
    laberinto->mat[*yIni][*xIni] = ENTRADA;

    ///DFS
    algoritmoGenerador(laberinto->mat, *xIni, 1, laberinto->cf, laberinto->cc, &ultimoX, &ultimoY, dx, dy, dir);

    //Asegurar un camino a la salida.
    if (ultimoY == 1)
            laberinto->mat[0][ultimoX] = SALIDA;
    else if (ultimoY == laberinto->cf - 2)
        laberinto->mat[laberinto->cf - 1][ultimoX] = SALIDA;
    else if (ultimoX == 1)
        laberinto->mat[ultimoY][0] = SALIDA;
    else if (ultimoX == laberinto->cc - 2)
        laberinto->mat[ultimoY][laberinto->cc - 1] = SALIDA;
    else
    {
        laberinto->mat[laberinto->cf - 2][laberinto->cc - 3] = CAMINO;
        laberinto->mat[laberinto->cf - 1][laberinto->cc - 3] = SALIDA;
    }

    return TODO_OK;

}

void algoritmoGenerador(char** mLaberinto, int x, int y, int filas, int columnas,  int* ultimoX, int* ultimoY,
                        int dx[], int dy[], int dir[])
{
    int i, r, temp, nx, ny;

    mLaberinto[y][x] = CAMINO;
    *ultimoX = x;
    *ultimoY = y;

    for(i = 0; i < 4; i ++)
    {
        r = rand() % 4; //Num al azar de 0 a 3

        temp = dir[i];
        dir[i] = dir[r];
        dir[r] = temp;
    }

    for(i = 0; i < 4; i ++)
    {
        nx = x + dx[dir[i]] * 2;
        ny = y + dy[dir[i]] * 2;

        if(esDirValida(mLaberinto, nx, ny, filas, columnas))
        {
            mLaberinto[ y + dy[dir[i]]  ] [ x + dx[dir[i]] ] = CAMINO;
            algoritmoGenerador(mLaberinto, nx, ny, filas, columnas, ultimoX, ultimoY, dx, dy, dir);
        }
        else
        {
            if(filas % 2 == 0 || columnas % 2 == 0)
                if( (ny == filas - 1 && nx <= columnas - 1) || (nx == columnas - 1 && ny <= filas - 1))
                    mLaberinto[ y + dy[dir[i]]  ] [ x + dx[dir[i]] ] = CAMINO;
        }
    }
}

int esDirValida(char** mLaberinto, int x, int y, int filas, int columnas)
{
    return x > 0 && x < columnas - 1 && y > 0 && y < filas - 1 && mLaberinto[y][x] == PARED;
}
