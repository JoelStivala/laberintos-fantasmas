#include "../Headers/laberinto.h"

//#define MAX(a,b) ((a)>(b)?(a):(b))

void acondicionarLaberinto(char** mat, int filas, int columnas);
int generarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni);
void algoritmoGenerador(tLaberinto* laberinto, int x, int y,
                        const int dx[], const int dy[], int dir[]);
int esDirGenLabValida(tLaberinto* laberinto, int posX, int posY);
void facilitarLaberinto(tLaberinto* laberinto);
void posicionarElementos(tLaberinto* laberinto, tConfig* config);
void aleatoriezarAparicionDeElem(tLaberinto* laberinto, int* x, int* y);
int laberintoGrabarEnArchivoTxt(tLaberinto* laberinto, const char* nomArch);
int cargarLaberinto(const char* nomArch, void* elem);

int inicializarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni, tConfig* config)
{
    int ret;

    laberinto->mat = (char**)crearMatriz(sizeof(char), config->filas, config->columnas);
    if(laberinto->mat == NULL)
        return ERR_MEMORIA;

    laberinto->cf = config->filas;
    laberinto->cc = config->columnas;

    acondicionarLaberinto(laberinto->mat, laberinto->cf, laberinto->cc);

    //Necesario para la aleatoriedad
    srand(time(NULL));

    ret = generarLaberinto(laberinto, xIni, yIni);

    if(ret != TODO_OK)
    {
        destruirMatriz( (void**)laberinto->mat, laberinto->cf);
        return ret;
    }

    facilitarLaberinto(laberinto);

    posicionarElementos(laberinto, config);

    ret = laberintoGrabarEnArchivoTxt(laberinto, LABERINTO_TXT);

    if(ret != TODO_OK)
    {
        ///No decidimos destruir la matriz, solo devolvemos el error.
        ///Aquel que lo recibe decide si la elimina
        return ret;
    }

    ///Ya tengo la memoria reservada para la matriz. La sobreescribo

    ret = cargarLaberinto(LABERINTO_TXT, laberinto);

    return ret;
}

void acondicionarLaberinto(char** mat, int filas, int columnas)
{
    int i, j;

    for(i = 0; i < filas; i ++)
        for(j = 0; j < columnas; j ++)
            mat[i][j] = BLOQUE;
}

int generarLaberinto(tLaberinto* laberinto, int* xIni, int* yIni)
{
    int r;
    // izquierda, derecha, arriba, abajo
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int dir[] = {0, 1, 2, 3};

    //Generar entrada al azar
    *yIni = 0;
    *xIni = 1 + rand() % (laberinto->cc - 2); //+1 y -1 para que no sea borde izq ni der. Del 1 al cc - 1
    laberinto->mat[*yIni][*xIni] = ENTRADA;

    ///DFS
    algoritmoGenerador(laberinto, *xIni, 1, dx, dy, dir);

    //Asegurar un camino a la salida.
    r = 1 + rand() % (laberinto->cc - 2);
    laberinto->mat[laberinto->cf - 2][r] = CAMINO;
    laberinto->mat[laberinto->cf - 1][r] = SALIDA;

    (*yIni)++;

    return TODO_OK;

}

void algoritmoGenerador(tLaberinto* laberinto, int x, int y,
                        const int dx[], const int dy[], int dir[])
{
    int i, r, temp, nx, ny;

    laberinto->mat[y][x] = CAMINO;

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

        if(esDirGenLabValida(laberinto, nx, ny))
        {
            laberinto->mat[ y + dy[dir[i]]  ] [ x + dx[dir[i]] ] = CAMINO;
            algoritmoGenerador(laberinto, nx, ny, dx, dy, dir);
        }
        else
        {
            if(laberinto->cf % 2 == 0 || laberinto->cc % 2 == 0)
                if( (ny == laberinto->cf - 1 && nx <= laberinto->cc - 1) || (nx == laberinto->cc - 1 && ny <= laberinto->cf - 1))
                    laberinto->mat[ y + dy[dir[i]]  ] [ x + dx[dir[i]] ] = CAMINO;
        }
    }
}

int esDirGenLabValida(tLaberinto* laberinto, int posX, int posY)
{
    return posX > 0 && posX < laberinto->cc - 1 && posY > 0 && posY < laberinto->cf - 1 && hayBloque(laberinto, posX, posY);
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

int laberintoGrabarEnArchivoTxt(tLaberinto* laberinto, const char* nomArch)
{
    FILE* pf = fopen(nomArch, "wt");
    int i;
    if(!pf)
        return ERR_ARCHIVO;

    for(i = 0; i < laberinto->cf; i ++)
        fprintf(pf, "%.*s\n", laberinto->cc, laberinto->mat[i]);

    printf("\n\nPUDO GRABAR\n\n");

    fclose(pf);
    return TODO_OK;
}

int cargarLaberinto(const char* nomArch, void* elem)
{
    char linea[TAM_LINEA];
    tLaberinto* laberinto;
    int i;
    FILE* pf = fopen(nomArch, "rt");

    if(!pf)
        return ERR_ARCHIVO;

    laberinto = elem;
    i = 0;
    while(fgets(linea, TAM_LINEA, pf) && i < laberinto->cf)
    {
        sscanf(linea, "%s" , laberinto->mat[i]);
        i++;
    }

    printf("\n\nPUDO CARGAR\n\n");

    fclose(pf);
    return TODO_OK;
}

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

int hayBloque(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '#';
}

int hayCamino(tLaberinto* laberinto, int posX, int posY)
{
    return laberinto->mat[posY][posX] == '.';
}

int esDirValida(tLaberinto* laberinto, int posX, int posY)
{
    if(posX >= 0 && posX < laberinto->cc - 1 &&
       posY >= 0 && posY <= laberinto->cf - 1)
    {
        return (!hayBloque(laberinto, posX, posY) ) ||
                (laberinto->mat[posY][posX] == ENTRADA) ||
                (laberinto->mat[posY][posX] == SALIDA);
    }

    return FALSE;
}
