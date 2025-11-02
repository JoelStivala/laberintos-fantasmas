#include "../Headers/fantasma.h"


void cargarPosicionesFantasmas(tVector* fantasmas, tLaberinto* laberinto)
{
    int i;
    int j;
    int movXY[2];

    tFantasma* fantasmaAux = fantasmas->v;

    for(i = 1 ; i < laberinto->cf -1 ; i++)
    {
        for(j = 1 ; j < laberinto->cc -1 ; j++)
        {
            if(laberinto->mat[i][j] == 'F')
            {
                fantasmaAux->posX = j;
                fantasmaAux->posY = i;
                fantasmaAux->vivo = 1;
                movXY[0] = fantasmaAux->posX;
                movXY[1] = fantasmaAux->posY;
                fantasmas->ce++;
                colaCrear(&fantasmaAux->colaMovimientos);
                colaEncolar(&fantasmaAux->colaMovimientos, movXY, sizeof(movXY));
                fantasmaAux++;
            }
        }
    }
}

void moverFantasmas(tFantasma* f, tJugador* j, tLaberinto* lab)
{
    int dx = 0, dy = 0;
    int movXY[2];

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

    movXY[0] = f->posX;
    movXY[1] = f->posY;

    colaEncolar(&f->colaMovimientos, movXY, sizeof(movXY));
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

void mostrarMovimientosFantasma(tVector *fantasmas)
{
    void* i;
    void* ult = (char*)fantasmas->v + fantasmas->ce * fantasmas->tamElem;
    int posXY[2];
    tFantasma* f;

    for (i = fantasmas->v; i < ult; i = (char*)i + fantasmas->tamElem)
    {
        f = (tFantasma*)i;
        while(!colaVacia(&f->colaMovimientos))
        {
            colaQuitar(&f->colaMovimientos, posXY, sizeof(posXY));
            printf("%d %d\t", posXY[0], posXY[1]);
        }
        printf("\n\n");

        colaVaciar(&f->colaMovimientos);
    }

}

