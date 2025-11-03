#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void crearArbolBin(tArbol *raiz)
{
    *raiz = NULL;
}

int insertarEnArbolBinRecursivo(tArbol *raiz, const void *info, unsigned bytes, cmp comparacion, accionDuplicado funcion)
{
    tNodoArbol *nue;
    int compare;

    if(*raiz == NULL) // caso base: lugar libre
    {
        nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
        if(!nue)
            return ERR_MEMORIA;

        nue->info = malloc(bytes);
        if(!nue->info)
        {
            free(nue);
            return ERR_MEMORIA;
        }

        memcpy(nue->info, info, bytes);
        nue->izq = NULL;
        nue->der = NULL;

        *raiz = nue;
        return TODO_OK;
    }

    compare = comparacion(info, (*raiz)->info);

    if(compare < 0)
        return insertarEnArbolBinRecursivo(&(*raiz)->izq, info, bytes, comparacion, NULL);

    if(compare > 0)
        return insertarEnArbolBinRecursivo(&(*raiz)->der, info, bytes, comparacion, NULL);

    return ERR_DUPLICADO;
}

int recorrerArbolBinPreorden(tArbol *raiz, accion funcion)
{
    if(*raiz){
        funcion((*raiz)->info);
        recorrerArbolBinPreorden(&(*raiz)->izq,funcion);
        recorrerArbolBinPreorden(&(*raiz)->der,funcion);
    }
    return TODO_OK;
}

int recorrerArbolBinPostorden(tArbol *raiz, accion funcion)
{
    if(*raiz){
        recorrerArbolBinPostorden(&(*raiz)->izq,funcion);
        recorrerArbolBinPostorden(&(*raiz)->der,funcion);
        funcion((*raiz)->info);
    }
    return TODO_OK;
}

int recorrerArbolBinInorden(tArbol *raiz, accion funcion)
{
    if(*raiz){
        recorrerArbolBinInorden(&(*raiz)->izq,funcion);
        funcion((*raiz)->info);
        recorrerArbolBinInorden(&(*raiz)->der,funcion);
    }
    return TODO_OK;
}

void* busquedaBin(tArbol *raiz, void *clave, unsigned bytes, cmp comparacion)
{
    int compare;
    if(*raiz==NULL)
        return NULL;
    compare=comparacion(clave,(*raiz)->info);
    if(compare==0)
    {
        memcpy(clave,(*raiz)->info, MIN(bytes,(*raiz)->tam));
        return clave;
    }
    if(compare>0)
        return busquedaBin(&(*raiz)->der,clave,bytes,comparacion);
    return busquedaBin(&(*raiz)->izq,clave,bytes,comparacion);
}

int arbolVacio(const tArbol *raiz)
{
    return *raiz==NULL ? 1 : 0;
}

int arbolLleno(const tArbol *raiz, unsigned bytes)
{
    tNodoArbol *aux;
    aux = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!aux)
        return 1;
    aux->info=malloc(bytes);
    if(!aux->info)
    {
        free(aux);
        return 1;
    }
    free(aux->info);
    free(aux);
    return 0;
}

void vaciarArbol(tArbol *raiz)
{
    tNodoArbol *aux;
    if(*raiz)
    {
        vaciarArbol(&(*raiz)->izq);
        vaciarArbol(&(*raiz)->der);
        aux = *raiz;
        *raiz = aux->der;
        free(aux->info);
        free(aux);
    }
}
