#include "Lista.h"

void listaCrear(tLista* lista)
{
    *lista = NULL;
}

void listaVaciar(tLista *lista)
{
    tNodo* elim;

    while(*lista)
    {
        elim = *lista;
        *lista = elim->sig;
        free(elim->info);
        free(elim);
    }
}


int listaInsertarInicio(tLista* lista, void* el, size_t tamElem)
{
    tNodo* nue = malloc(sizeof(tNodo));

    if(!nue)
    {
        return ERR_MEMORIA;
    }

    nue->info = malloc(tamElem);

    if(!nue->info)
    {
        free(nue);
        return ERR_MEMORIA;
    }

    memcpy(nue->info, el, tamElem);
    nue->tamElem = tamElem;
    nue->sig = *lista;
    *lista = nue;

    return 0;
}

int listaInsertarFin(tLista* lista, void* el, size_t tamElem)
{
    tNodo* nue = malloc(sizeof(tNodo));
    tNodo* aux = *lista;

    if(!nue)
        return ERR_MEMORIA;

    nue->info = malloc(tamElem);

    if(!nue->info)
    {
        free(nue);
        return ERR_MEMORIA;
    }

    memcpy(nue->info, el, tamElem);
    nue->tamElem = tamElem;
    nue->sig = NULL;

    if(aux != NULL)
    {
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nue;
    }
    else
    {
        *lista = nue;
    }

    return 0;
}
