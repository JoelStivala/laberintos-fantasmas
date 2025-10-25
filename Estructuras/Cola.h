#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/common.h"

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;

///PRIMITIVAS
void colaCrear(tCola *cola);
int colaEncolar(tCola *cola, const void *info, unsigned bytes);
int colaVerPrimero(const tCola *cola, void *info, unsigned bytes);
int colaQuitar(tCola *cola, void *info, unsigned bytes);
int colaVacia(const tCola *cola);
void colaVaciar(tCola *cola);

#endif // COLA_H_INCLUDED
