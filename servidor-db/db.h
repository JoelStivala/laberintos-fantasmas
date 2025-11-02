#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arbol.h"
#include "Lista.h"

#define TODO_OK 0
#define ERR_ARCHIVO 1

typedef struct {
    char nombre[51];
} tUsuario;

typedef struct {
    char nombreJugador[51];
    int idPartida;
    int puntuacion;
    int movimientos;
    char resultado;
} tPartida;


int obtenerMaxIdPartida(const char* nombreJugador);
int inicializarBD(tArbol* arbolUsuarios);
int guardarUsuario(tArbol* arbolUsuarios, const char* nombre);
int guardarPartida(const char* nombreJugador, int puntuacion, int movimientos, char resultado);

void mostrarRankingSimple();

#endif
