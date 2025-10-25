#include "../Headers/fantasma.h"


void cargarPosicionesFantasmas(tVector* fantasmas, tLaberinto* laberinto)
{
    int i;
    int j;
    tFantasma* fantasmaAux = fantasmas->v;

    for(i = 1 ; i < laberinto->cf -1 ; i++)
    {
        for(j = 1 ; j < laberinto->cc -1 ; j++)
        {
            if(laberinto->mat[i][j] == 'F')
            {
                fantasmaAux->posX = j;
                fantasmaAux->posY = i;
                fantasmas->ce++;
                colaCrear(&fantasmaAux->colaMovimientos);
                fantasmaAux++;
            }
        }
    }
}

void moverFantasmas(tFantasma* f, tJugador* j, tLaberinto* lab)
{
    int dx = 0, dy = 0;
    int movYX[2];

    if (j->posX > f->posX)
        dx = 1;
    else if (j->posX < f->posX)
        dx = -1;

    if (j->posY > f->posY)
        dy = 1;
    else if (j->posY < f->posY)
        dy = -1;

    if (!hayBloque(lab, f->posX, f->posY + dy))
        f->posY += dy;
    else if (!hayBloque(lab, f->posX + dx, f->posY))
        f->posX += dx;

    movYX[0] = f->posY;
    movYX[1] = f->posX;

    colaEncolar(&f->colaMovimientos, movYX, sizeof(movYX));
}

void liberarMovimientosFantasmas(tVector* fantasmas)
{
    void* i;
    void* ult = (char*)fantasmas->v + fantasmas->ce * fantasmas->tamElem;
    tFantasma* f;

    for (i = fantasmas->v; i < ult; i = (char*)i + fantasmas->tamElem)
    {
        f = (tFantasma*)i;
        colaVaciar(&f->colaMovimientos);
    }
}

void liberarMovimientosFantasma(tFantasma* fantasma)
{
    colaVaciar(&fantasma->colaMovimientos);
}

void mostrarMovimientosFantasma(tVector *fantasmas)
{
    void* i;
    void* ult = (char*)fantasmas->v + fantasmas->ce * fantasmas->tamElem;
    int posYX[2];
    tFantasma* f;

    for (i = fantasmas->v; i < ult; i = (char*)i + fantasmas->tamElem)
    {
        f = (tFantasma*)i;
        while(!colaVacia(&f->colaMovimientos))
        {
            colaQuitar(&f->colaMovimientos, posYX, sizeof(posYX));
            printf("%d %d\t", posYX[0], posYX[1]);
        }
        printf("\n\n");
    }

}
