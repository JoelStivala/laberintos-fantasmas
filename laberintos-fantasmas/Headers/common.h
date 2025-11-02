#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX(A,B) ((A)>(B)?(A):(B))
#define MIN(A,B) ((A)<(B)?(A):(B))

#define TODO_OK 0
#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2

typedef struct
{
    int cantidad;
    int suma;
}tPromedio;

typedef int (*TxtAMem)(FILE* pf, void* elem);

typedef struct sNodo
{
    void* info;
    size_t tamElem;
    struct sNodo* sig;
} tNodo;

int cargarRegistroMemoria(const char* nomTxt, void* elem, TxtAMem txtAMem);
void pauseEnter();
int sinDuplicados(void* dest, const void* src);

///PUNTEROS A FUNCIONES (definiciones)

typedef int(*cmp)(const void*,const void*);
typedef void(*reduccion) (const void*,void *);
typedef void(*accion) (void*);
typedef int(*accionDuplicado) (void*,const void*);
typedef int(*condicion) (void*);

#endif // COMMON_H_INCLUDED
