#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

typedef struct
{
    int posX;
    int posY;
}tJugador;

void movimiento(tJugador* jugador, char input);

#endif // JUGADOR_H_INCLUDED
