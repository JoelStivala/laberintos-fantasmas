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
    if(*raiz==NULL)
    {
        nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
        if(!nue)
            return ERR_MEMORIA;
        nue->info=malloc(bytes);
        if(!nue->info)
        {
            free(nue);
            return ERR_MEMORIA;
        }
        memcpy(nue->info,info,bytes);
        nue->izq=NULL;
        nue->der=NULL;
        *raiz=nue;
        return TODO_OK;
    }
    compare=comparacion(info,(*raiz)->info);
    if(compare<0)
        return insertarEnArbolBin(&(*raiz)->izq,info,bytes,comparacion,funcion);
    if(compare>0)
        return insertarEnArbolBin(&(*raiz)->der,info,bytes,comparacion,funcion);
    return funcion((*raiz)->info,info);
}

int insertarEnArbolBin(tArbol *raiz, const void *info, unsigned bytes, cmp comparacion, accionDuplicado funcion)
{
    tNodoArbol *nue;
    int compare;
    while(*raiz){
        compare=comparacion(info,(*raiz)->info);
        if(compare==0)
            return funcion((*raiz)->info,info);
        if(compare<0)
            raiz = &(*raiz)->izq;
        else
            raiz = &(*raiz)->der;
    }
    nue = (tNodoArbol*)malloc(sizeof(tNodoArbol));
    if(!nue)
        return ERR_MEMORIA;
    nue->info=malloc(bytes);
    if(!nue->info)
    {
        free(nue);
        return ERR_MEMORIA;
    }
    memcpy(nue->info,info,bytes);
    nue->izq=NULL;
    nue->der=NULL;
    *raiz=nue;
    return TODO_OK;
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
///ejercicios extras para entregas
int contarHojas(tArbol *raiz)
{
    int hojas=0;
    if(*raiz==NULL)
        return 0;
    if((*raiz)->izq==NULL && (*raiz)->der==NULL)
        return 1;
    hojas+=contarHojas(&(*raiz)->izq);
    return hojas+contarHojas(&(*raiz)->der);
}

int contarNoHojas(tArbol *raiz)
{
    int noHojas=0;
    if(*raiz==NULL)
        return 0;
    if((*raiz)->izq!=NULL || ((*raiz)->der!=NULL))
        noHojas++;
    noHojas+=contarNoHojas(&(*raiz)->izq);
    return noHojas+contarNoHojas(&(*raiz)->der);
}

int contarNodos(tArbol *raiz)
{
    int cantNodos=0;
    if(*raiz==NULL)
        return 0;
    cantNodos++;
    cantNodos+=contarNodos(&(*raiz)->izq);
    return cantNodos+contarNodos(&(*raiz)->der);
}

tNodoArbol* buscarClaveMayor(tArbol *raiz)
{
    if(*raiz==NULL)
        return NULL;
    if((*raiz)->der==NULL)
        return *raiz;
    return buscarClaveMayor(&(*raiz)->der);
}

tNodoArbol* buscarClaveMenor(tArbol *raiz)
{
    if(*raiz==NULL)
        return NULL;
    if((*raiz)->izq==NULL)
        return *raiz;
    return buscarClaveMenor(&(*raiz)->izq);
}

int recorrerSubarbolDer(tArbol *raiz, condicion funcion)
{
    if(*raiz==NULL)
        return 0;
    return _accionSubarbolDer(&(*raiz)->der,funcion);
}

int _accionSubarbolDer(tArbol *raiz,condicion funcion)
{
    int condicionCumplida=0;
    if(*raiz==NULL)
        return 0;
    condicionCumplida+=funcion((*raiz)->info);
    condicionCumplida+=_accionSubarbolDer(&(*raiz)->izq,funcion);
    return condicionCumplida+_accionSubarbolDer(&(*raiz)->der,funcion);
}

int contarNodosPorClave(tArbol *raiz, const void *clave, int fnc(void*,const void*))
{
    int cantidad=0;
    if(*raiz==NULL)
        return 0;
    cantidad+=fnc((*raiz)->info,clave);
    cantidad+=contarNodosPorClave(&(*raiz)->izq,clave,fnc);
    return cantidad+contarNodosPorClave(&(*raiz)->der,clave,fnc);
}

float promedioConClavePar(tArbol *raiz, tPromedio *p ,void promedio(void*,tPromedio*))
{
    if(*raiz==NULL)
        return 0;
    promedio((*raiz)->info,p);
    promedioConClavePar(&(*raiz)->izq,p,promedio);
    promedioConClavePar(&(*raiz)->der,p,promedio);
    if(p->cantidad)
        return (float)p->suma/p->cantidad;
    return 0;
}


///pendiete de revision, idem el de contar por no clave
int buscarPorNoClave(tArbol *raiz, void *noClave, unsigned bytes, int algo(void *,const void*))
{
    if(*raiz==NULL)
        return 0;
    if(algo((*raiz)->info,noClave))
    {
        memcpy(noClave,(*raiz)->info,MIN(bytes,(*raiz)->tam));
        return TODO_OK;
    }
    if((*raiz)->izq && (*raiz)->der==NULL)
        return buscarPorNoClave(&(*raiz)->izq,noClave,bytes,algo);
    if((*raiz)->izq==NULL && (*raiz)->der)
        return buscarPorNoClave(&(*raiz)->izq,noClave,bytes,algo);
    return 0;
}

///////////////////////////////////////////////////////////////
///no hace falta los +=, las asignaciones son para evitar llamadas en el retorno
int alturaArbol(tArbol *raiz)
{
    int hi = 0, hd = 0;
    if(*raiz==NULL)
        return 0;
    hi = alturaArbol(&(*raiz)->izq);
    hd = alturaArbol(&(*raiz)->der);
    return MAX(hi+1,hd+1);
}

int nivelArbol(tArbol *raiz)
{
    int hi = 0, hd = 0;
    if(*raiz==NULL)
        return -1;
    hi = nivelArbol(&(*raiz)->izq);
    hd = nivelArbol(&(*raiz)->der);
    return (hi>hd) ? hi+1 : hd+1;
}

int recorrerHastaNivel(tArbol *raiz, int nivel,void accion(void*))
{
    if(*raiz==NULL || nivel==-1)
        return TODO_OK;
    accion((*raiz)->info);
    recorrerHastaNivel(&(*raiz)->izq,nivel-1,accion);
    return recorrerHastaNivel(&(*raiz)->der,nivel-1,accion);
}

int recorrerNivel(tArbol *raiz, int nivel, void accion(void*))
{
    if(*raiz==NULL)
        return TODO_OK;
    if(nivel==0)
    {
        accion((*raiz)->info);
        return TODO_OK;
    }
    recorrerNivel(&(*raiz)->izq,nivel-1,accion);
    return recorrerNivel(&(*raiz)->der,nivel-1,accion);
}


///revisar si se puede sin la variable actual
int recorrerDesdeNivel(tArbol *raiz, int nivel, void accion(void*))
{
    if(*raiz==NULL)
        return TODO_OK;
    if(nivel<=0)
        accion((*raiz)->info);
    recorrerDesdeNivel(&(*raiz)->izq,nivel-1,accion);
    return recorrerDesdeNivel(&(*raiz)->der,nivel-1,accion);
}

///////////////////////////////////////////////////////////////
int esArbolBinCompleto(tArbol *raiz)
{
    int nodosArbol = contarNodos(raiz);
    int potencia = pow(2,alturaArbol(raiz))-1;
    return nodosArbol == potencia ? COMPLETO : NO_COMPLETO;
}
///PENDIENTE DE REVISION, IDEM AVL
int esArbolBinBalanceado(tArbol *raiz)
{
    if(*raiz==NULL)
        return BALANCEADO;
    return BALANCEADO;
}

int esAVL(tArbol *raiz)
{
    return AVL;
}

int eliminarNodo(tArbol *raiz, void *clave, unsigned bytes, int cmp(const void*,const void*))
{
    int comparacion;
    tNodoArbol *aux;
    if(*raiz==NULL)
        return TODO_OK;
    comparacion = cmp(clave,(*raiz)->info);
    if(comparacion==0)
    {
        if((*raiz)->izq==NULL && (*raiz)->der==NULL)
        {
            memcpy(clave,(*raiz)->info,MIN(bytes,(*raiz)->tam));
            aux=*raiz;
            *raiz=aux->der;
            free(aux->info);
            free(aux);
            return TODO_OK;
        }
        else
            return eliminarRaiz(raiz,clave);
    }
    if(comparacion>0)
        return eliminarNodo(&(*raiz)->der,clave,bytes,cmp);
    return eliminarNodo(&(*raiz)->izq,clave,bytes,cmp);
}

int eliminarRaiz(tArbol* raiz, void *clave, unsigned bytes)
{
    tArbol *p;
    tNodoArbol *nodo;
    int hi = nivelArbol(&(*raiz)->izq);
    int hd = nivelArbol(&(*raiz)->der);
    if(hi>hd)
    {
        p = &(*raiz)->izq;
        while((*p)->der)
            p=&(*p)->der;
    }
    else
    {
        p = &(*raiz)->der;
        while((*p)->izq)
            p=&(*p)->izq;
    }
    nodo=*p;
    memcpy(clave,nodo->info,MIN(nodo->tam,bytes));
    if(nodo->izq)
        *p=nodo->izq;
    else
        *p=nodo->der;
    memcpy((*raiz)->info,nodo->info,MIN(nodo->tam,bytes));
    free(nodo->info);
    free(nodo);
    return TODO_OK;
}

