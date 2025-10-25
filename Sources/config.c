#include "../Headers/config.h"

int cargarConfiguracion(FILE* pf, void* elem)
{
    char linea[255];
    tConfig* config = elem;

    fgets(linea, 255, pf);
    sscanf(linea, "filas: %d\n", &config->filas);

    fgets(linea, 255, pf);
    sscanf(linea, "columnas: %d\n", &config->columnas);

    fgets(linea, 255, pf);
    sscanf(linea, "vidas_inicio: %d\n", &config->vidasInicio);

    fgets(linea, 255, pf);
    sscanf(linea, "maximo_numero_fantasmas: %d\n", &config->maxNumeroFantasmas);

    fgets(linea, 255, pf);
    sscanf(linea, "maximo_numero_premios: %d\n", &config->maxNumeroPremios);

    fgets(linea, 255, pf);
    sscanf(linea, "maximo_vidas_extra: %d\n", &config->maxVidasExtra);

    return TODO_OK;
}

void inicializarConfiguracion(tConfig* config)
{
    cargarRegistroMemoria("./Files/config.txt", config, cargarConfiguracion);
}
