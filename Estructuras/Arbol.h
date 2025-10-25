#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/common.h"

#define EXITO 1
#define FALLO_MALLOC 0
#define DUPLICADO 0
#define ARBOL_VACIO -1
#define NO_EXISTE 3

typedef struct sNodoArbol
{
  void * info;
  unsigned tamEl;
  struct sNodoArbol * izq,
          * der;
}tNodoArbol;

typedef tNodoArbol* tArbol;

typedef int(*tCmp) (const void*, const void*);
typedef void (*tPrnt) (const void*);


void crearArbol (tArbol * ar);
unsigned obtenerAltura (tArbol * ar);
unsigned obtenerNivelArbol (tArbol * ar);
unsigned short insertarEnArbolR (tArbol * a, const void * elemento, unsigned esize, tCmp cmp);
void mostrarEnOrden (tArbol * a, tPrnt mostrar);
void mostrarEnPreOrden (tArbol * a, tPrnt mostrar);
void mostrarEnPostOrden (tArbol * a, tPrnt mostrar);

void verHastaNivel (tArbol * ar, int nivel, tPrnt mostrar);
void vaciarArbol(tArbol * ar);
void verNivelNodos (tArbol * ar, int nivel, tPrnt mostrar);
void verDesdeNivelNodos (tArbol * ar, int nivel, tPrnt mostrar);

tNodoArbol **buscarNodoArbol (tArbol * a,void * elemento, unsigned esize, tCmp cmp);
tNodoArbol **buscarMenor(tArbol *ar);
tNodoArbol **buscarMayor(tArbol *ar);

int eliminarNodo(tArbol *ar, void *clave, unsigned tamElem, tCmp cmp);
int eliminarRaizNodoArbolBinBusq(tArbol *ar);
int eliminarRaizNodoArbolBinBusqEnv(tArbol *ar, void *elem, unsigned tamElem, tCmp cmp);

#endif // ARBOL_H_INCLUDED
