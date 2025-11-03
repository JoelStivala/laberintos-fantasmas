#include "Vector.h"

int vectorCrear(tVector* vec, size_t tamElem, int ce)
{
    vec->v = malloc(tamElem * ce);

    if(!vec->v)
        return ERR_MEMORIA;

    vec->tamElem = tamElem;
    vec->ce = 0;
    vec->cap = ce;

    return TODO_OK;
}

int vectorInsertarAlFinal(tVector* vec, void* el)
{
    void* finVec;

    if(vec->ce == vec->cap)
        return VEC_LLENO;

    finVec = vec->v + (vec->ce * vec->tamElem);

    memcpy(finVec, el, vec->tamElem);
    vec->ce++;

    return TODO_OK;
}

void vectorDestruir(tVector* vec)
{
    free(vec->v);
    vec->cap = 0;
    vec->ce = 0;
    vec->tamElem = 0;
}

int vectorEliminarPosicion(tVector* vec, int pos)
{
    void* i;
    void* ult = vec->v + ((vec->ce - 1) * vec->tamElem) ;

    if (pos < 0 || pos >= vec->ce)
        return ERR_RANGO;


    for (i = vec->v + pos * vec->tamElem; i < ult; i += vec->tamElem)
    {
        memcpy(i, i + vec->tamElem, vec->tamElem);
    }


    vec->ce--;

    return TODO_OK;
}
