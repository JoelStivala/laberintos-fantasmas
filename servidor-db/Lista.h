#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

typedef tNodo* tLista;

void listaCrear(tLista* lista);
void listaVaciar(tLista*lista);
int listaInsertarInicio(tLista* lista, void* el, size_t tamElem);
int listaInsertarFin(tLista* lista, void* el, size_t tamElem);

#endif // LISTA_H_INCLUDED
