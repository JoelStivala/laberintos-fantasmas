#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdio.h>
#include "common.h"
typedef struct
{
    int filas;
    int columnas;
    int vidasInicio;
    int maxNumeroFantasmas;
    int maxNumeroPremios;
    int maxVidasExtra;
} tConfig;

int cargarConfiguracion(FILE* pf, void* elem);
void inicializarConfiguracion(tConfig* config);
#endif // CONFIG_H_INCLUDED
