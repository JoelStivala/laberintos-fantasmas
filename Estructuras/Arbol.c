#include "../Estructuras/Arbol.h"

void crearArbol (tArbol * ar)
{
 *ar = NULL;
}

unsigned obtenerAltura (tArbol * ar)
{
 unsigned hIzq, hDer;

 if(!*ar)
   return 0;

 hIzq = obtenerAltura(&(*ar)->izq);
 hDer = obtenerAltura(&(*ar)->der);
 return 1 + MAX(hIzq, hDer);
}


unsigned obtenerNivelArbol (tArbol * ar)
{
 return obtenerAltura(ar) - 1;
}

unsigned short insertarEnArbolR (tArbol * a, const void * elemento, unsigned esize, tCmp cmp)
{

 int resultado;

 if (*a)
 {
  resultado = cmp(elemento, (*a)->info);
  if (resultado < 0)
     return insertarEnArbolR(&(*a)->izq, elemento, esize, cmp);
   else if (resultado > 0)
    return insertarEnArbolR(&(*a)->der, elemento, esize, cmp);
   else
     return DUPLICADO;
 }

 *a = (tNodoArbol*)malloc(sizeof(tNodoArbol));
 if (!(*a))
    return FALLO_MALLOC;

 (*a)->info = malloc(esize);
 if (!((*a)->info))
 {
  free(*a);
  return FALLO_MALLOC;
 }

 memcpy((*a)->info, elemento, esize);
 (*a)->tamEl = esize;
 (*a)->izq = NULL;
 (*a)->der = NULL;

 return EXITO;

}

void mostrarEnOrden (tArbol * a, tPrnt mostrar)
{
 if (*a)
 {
  mostrarEnOrden(&(*a)->izq, mostrar);
  mostrar((*a)->info);
  mostrarEnOrden(&(*a)->der, mostrar);
 }

}

/////////////////////////////////////////////////////////////////////////////

void mostrarEnPreOrden (tArbol * a, tPrnt mostrar)
{
 if (*a)
 {
  mostrar((*a)->info);
  mostrarEnPreOrden(&(*a)->izq, mostrar);
  mostrarEnPreOrden(&(*a)->der, mostrar);
 }

}

/////////////////////////////////////////////////////////////////////////////

void mostrarEnPostOrden (tArbol * a, tPrnt mostrar)
{
 if (*a)
 {
  mostrarEnPostOrden(&(*a)->izq, mostrar);
  mostrarEnPostOrden(&(*a)->der, mostrar);
  mostrar((*a)->info);
 }

}

/////////////////////////////////////////////////////////////////////////////

void verHastaNivel (tArbol * ar, int nivel, tPrnt mostrar)
{
 if (!*ar || nivel < 0)
     return;

 mostrar((*ar)->info);
 verHastaNivel(&(*ar)->izq, nivel-1, mostrar);
 verHastaNivel(&(*ar)->der, nivel-1, mostrar);

}

void verNivelNodos (tArbol * ar, int nivel, tPrnt mostrar)
{
    if(!*ar)
    {
        return;
    }

    if(nivel == 0)
    {
        mostrar((*ar)->info);
        return;
    }

    verNivelNodos(&(*ar)->izq, nivel-1, mostrar);
    verNivelNodos(&(*ar)->der, nivel -1, mostrar);

    return;
}

void verDesdeNivelNodos (tArbol * ar, int nivel, tPrnt mostrar)
{
    if(!*ar)
    {
        return;
    }

    if(nivel <= 0)
    {
        mostrar((*ar)->info);
    }

    verDesdeNivelNodos(&(*ar)->izq, nivel - 1, mostrar);
    verDesdeNivelNodos(&(*ar)->der, nivel - 1, mostrar);

    return;
}

int eliminarNodo(tArbol *ar, void *clave, unsigned tamElem, tCmp cmp)
{
    tNodoArbol **elim = buscarNodoArbol(ar,clave, tamElem, cmp);

    if(!*elim)
    {
        return NO_EXISTE;
    }

    if(!(*ar)->izq && !(*ar)->der)
    {
        free((*ar)->info);
        free(*ar);
        *ar = NULL;
    }else
    {
        eliminarRaizNodoArbolBinBusq(elim);
    }

    return EXITO;
}

int eliminarRaizNodoArbolBinBusq(tArbol *ar)
{
    tNodoArbol **remp, *elim;

    if(!(*ar))
    {
        return ARBOL_VACIO;
    }
    remp = obtenerAltura(&(*ar)->izq) > obtenerAltura(&(*ar)->der) ?
           buscarMayor(&(*ar)->izq) : buscarMenor(&(*ar)->der);

    elim = *remp;
    (*ar)->info = elim->info;
    (*ar)->tamEl = elim->tamEl;

    *remp = elim->izq ? elim->izq : elim->der;

    free(elim);

    return EXITO;

}

tNodoArbol **buscarMenor(tArbol *ar)
{
    if(!*ar)
    {
        return NULL;
    }

    while((*ar)->izq)
    {
        ar = &(*ar)->izq;
    }

    return (tNodoArbol**)ar;
}

tNodoArbol **buscarMayor(tArbol *ar)
{
    if(!*ar)
    {
        return NULL;
    }

    while((*ar)->der)
    {
        ar = &(*ar)->der;
    }

    return (tNodoArbol**)ar;
}

tNodoArbol **buscarNodoArbol (tArbol * a,void * elemento, unsigned esize, tCmp cmp)
{

 int resultado;

 if (*a && (resultado = cmp(elemento, (*a)->info)))
 {
  if (resultado < 0)
     return buscarNodoArbol(&(*a)->izq, elemento, esize, cmp);
   else if (resultado > 0)
    return buscarNodoArbol(&(*a)->der, elemento, esize, cmp);

 }
 if(!*a)
 {
     return NULL;
 }


 memcpy(elemento, (*a)->info, MIN((*a)->tamEl,esize));

 return (tNodoArbol**)a;
}


void vaciarArbol(tArbol * ar)
{

 if(!*ar)
   return;

 vaciarArbol(&(*ar)->izq);
 vaciarArbol(&(*ar)->der);
 free((*ar)->info);
 free(*ar);
 *ar = NULL;

}
