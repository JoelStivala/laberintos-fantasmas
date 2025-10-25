#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX(A,B) ((A)>(B)?(A):(B))
#define MIN(A,B) ((A)<(B)?(A):(B))

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2

typedef int (*TxtAMem)(FILE* pf, void* elem);

typedef struct sNodo
{
    void* info;
    size_t tamElem;
    struct sNodo* sig;
} tNodo;

int cargarRegistroMemoria(const char* nomTxt, void* elem, TxtAMem txtAMem);
void pauseEnter();

#endif // COMMON_H_INCLUDED
