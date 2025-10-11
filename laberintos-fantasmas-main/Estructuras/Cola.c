#include "Cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void colaCrear(tCola *cola)
{
    cola->pri=NULL;
    cola->ult=NULL;
}

int colaEncolar(tCola *cola, const void *info, unsigned bytes)
{
    tNodo *nue;
    nue = (tNodo*)malloc(sizeof(tNodo));

    if(nue==NULL)
        return 0;

    nue->info=malloc(bytes);

    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info,info,bytes);
    nue->tamanio=bytes;
    nue->sig=NULL;//por ser el utlimo, no tiene a nadie detras ¡¡SIEMPRE!!

    if(cola->pri==NULL)
        cola->pri=nue;
    else
        cola->ult->sig=nue;//asigno al siguiente del ultimo al que tengo detras de la cola

    cola->ult=nue;

    return 1;
}

int colaVerPrimero(const tCola *cola, void *info, unsigned bytes)
{
    if(cola->pri==NULL)
        return 0;
    memcpy(info,cola->pri->info,MIN(bytes,cola->pri->tamanio));
    return 1;
}

int colaQuitar(tCola *cola, void *info, unsigned bytes)
{
    tNodo *aux;
    if(cola->pri==NULL)
        return 0;
    aux = cola->pri;
    memcpy(info,aux->info,MIN(aux->tamanio,bytes));
    //memcpy(info,cola->pri->info,MIN(bytes,cola->pri->tamanio));
    //aux=cola->pri;
    cola->pri=aux->sig;
    free(aux->info);
    free(aux);
    return 1;
}


int colaVacia(const tCola *cola)
{
    return cola->pri==NULL;
}

void colaVaciar(tCola *cola)
{
    tNodo *aux;
    while(cola->pri)
    {
        aux = cola->pri;
        cola->pri=aux->sig;
        free(aux->info);
        free(aux);
    }
    //cola->ult=cola->pri; haria falta?
}
