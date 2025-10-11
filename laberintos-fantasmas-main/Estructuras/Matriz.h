#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdlib.h>

void** crearMatriz(size_t tamElem, int filas, int columnas);
void destruirMatriz(void** mat, int filas);

#endif // MATRIZ_H_INCLUDED
