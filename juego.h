#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "jugador.h"
#include "laberinto.h"
#include "fantasma.h"

int mostrarMenu();
void draw(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas);
void procesarCelda(tJugador* jugador, char* celda);

#endif // JUEGO_H_INCLUDED
