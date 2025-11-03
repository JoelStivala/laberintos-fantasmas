#include "../Headers/common.h"

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

void clearScreen()
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void pauseEnter() {
    printf("Presiona Enter para continuar...");
    fflush(stdin);
    getchar();
}

int sinDuplicados(void* dest, const void* src)
{
    return 0;
}

