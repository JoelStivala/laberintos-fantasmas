#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>

typedef struct
{
    void* v;
    size_t tamElem;
    int ce;
    int cap;
} tVector;

#endif // VECTOR_H_INCLUDED
