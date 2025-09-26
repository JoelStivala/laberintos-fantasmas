#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2

typedef int (*TxtAMem)(FILE* pf, void* elem);

int cargarRegistroMemoria(const char* nomTxt, void* elem, TxtAMem txtAMem);
void** crearMatriz(size_t tamElem, int filas, int columnas);
void destruirMatriz(void** mat, int filas);
#endif // COMMON_H_INCLUDED
