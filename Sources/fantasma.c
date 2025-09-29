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
                fantasmaAux++;
            }
        }
    }
}

void moverFantasmas(tFantasma* f, tJugador* j, tLaberinto* lab)
{
    int dx = 0, dy = 0;

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
}

