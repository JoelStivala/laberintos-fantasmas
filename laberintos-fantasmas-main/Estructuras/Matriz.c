#include "Matriz.h"

void** crearMatriz(size_t tamElem, int filas, int columnas)
{
    void** mat = malloc(sizeof(void*) * filas);

    if(!mat)
    {
        return NULL;
    }

    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++)
    {
        *i = malloc(tamElem * columnas);

        if(!*i)
        {
            destruirMatriz(mat, i - mat);
            return NULL;
        }
    }

    return mat;
}

void destruirMatriz(void** mat, int filas)
{
    if(!mat) return;
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++)
    {
        free(*i);
    }

    free(mat);
}
