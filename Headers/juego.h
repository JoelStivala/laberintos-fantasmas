#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "jugador.h"
#include "laberinto.h"
#include "fantasma.h"
#include "common.h"
#include "db.h"
#include "../Estructuras/Cola.h"
#include "../Estructuras/Arbol.h"

int mostrarMenu();
void draw(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas);
void procesarCelda(tJugador* jugador, tVector* fantasmas, char* celda);
void inicializarJuego(tConfig* config, tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas);

void gameLoop(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas, const char* nombreJugador);
void ingresoUsuario();

void pauseEnter();

#endif // JUEGO_H_INCLUDED
