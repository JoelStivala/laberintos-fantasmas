#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#include "../Headers/common.h"

#define VEC_LLENO 1
#define ERR_RANGO 2

typedef struct
{
    void* v;
    size_t tamElem;
    int ce;
    int cap;
} tVector;

int vectorCrear(tVector* vec, size_t tamElem, int ce);
int vectorInsertarAlFinal(tVector* vec, void* el);
int vectorEliminarPosicion(tVector* vec, int pos);
void vectorDestruir(tVector* vec);

#endif // VECTOR_H_INCLUDED
