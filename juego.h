#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "jugador.h"
#include "laberinto.h"

int mostrarMenu();
void draw(tLaberinto* laberinto, tJugador* jugador);

#endif // JUEGO_H_INCLUDED
