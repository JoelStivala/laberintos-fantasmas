#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "jugador.h"
#include "laberinto.h"
#include "fantasma.h"
#include "common.h"
#include "../Estructuras/Cola.h"

int mostrarMenu();
void draw(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas);
void procesarCelda(tJugador* jugador, vFantasmas* fantasmas, char* celda);
void inicializarJuego(tConfig* config, tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas);
void gameLoop(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas);

void pauseEnter();

#endif // JUEGO_H_INCLUDED
