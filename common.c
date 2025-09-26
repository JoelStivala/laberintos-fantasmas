#include "common.h"

int cargarRegistroMemoria(const char* nomTxt, void* elem, TxtAMem txtAMem)
{
    FILE* pf = fopen(nomTxt, "rt");

    if(!pf)
    {
        return ERR_ARCHIVO;
    }

    txtAMem(pf, elem);

    fclose(pf);
    return TODO_OK;
}

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
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++)
    {
        free(*i);
    }

    free(mat);
}
