#include "./db.h"

int obtenerMaxIdPartida(const char* nombreJugador)
{
    FILE* pf = fopen("../../Files/partidas.dat", "rb");
    tPartida partida;
    int maxId = 0;

    if(!pf)
        return 0;

    while(fread(&partida, sizeof(tPartida), 1, pf) == 1)
    {
        if(strcmp(partida.nombreJugador, nombreJugador) == 0)
        {
            if(partida.idPartida > maxId)
                maxId = partida.idPartida;
        }
    }

    fclose(pf);
    return maxId;
}


int compararUsuarios(const void* u1, const void* u2)
{
    return strcmp(((tUsuario*)u1)->nombre, ((tUsuario*)u2)->nombre);
}

int inicializarBD(tArbol* arbolUsuarios)
{
    FILE* pf = fopen("../../Files/usuarios.dat", "rb");
    tUsuario usuario;

    crearArbolBin(arbolUsuarios);
    if(!pf)
        return TODO_OK;

    while(fread(&usuario, sizeof(tUsuario), 1, pf) == 1)
        insertarEnArbolBinRecursivo(arbolUsuarios, &usuario, sizeof(tUsuario), compararUsuarios,sinDuplicados);

    fclose(pf);
    return TODO_OK;
}

int guardarUsuario(tArbol* arbolUsuarios, const char* nombre)
{
    FILE* pf;
    tUsuario nuevoUsuario;
    strcpy(nuevoUsuario.nombre, nombre);

    int resultado = insertarEnArbolBinRecursivo(arbolUsuarios, &nuevoUsuario, sizeof(tUsuario), compararUsuarios, NULL);
    if(resultado == ERR_DUPLICADO)
        return ERR_DUPLICADO;

    if(resultado != TODO_OK)
        return resultado;

    pf = fopen("../../Files/usuarios.dat", "ab");
    if(!pf)
        return ERR_ARCHIVO;

    fwrite(&nuevoUsuario, sizeof(tUsuario), 1, pf);
    fclose(pf);

    return TODO_OK;
}

int guardarPartida(const char* nombreJugador, int puntuacion, int movimientos, char resultado)
{
    FILE* pf;
    tPartida partida;

    int maxId = obtenerMaxIdPartida(nombreJugador);

    pf = fopen("../../Files/partidas.dat", "ab");
    if(!pf)
        return ERR_ARCHIVO;

    strcpy(partida.nombreJugador, nombreJugador);
    partida.idPartida = maxId + 1;
    partida.puntuacion = puntuacion;
    partida.movimientos = movimientos;
    partida.resultado = resultado;

    fwrite(&partida, sizeof(tPartida), 1, pf);
    fclose(pf);

    return TODO_OK;
}

void mostrarRankingSimple()
{
    system("cls || clear");
    FILE* pf = fopen("../../Files/partidas.dat", "rb");
    tPartida partida;

    if(!pf)
    {
        printf("No hay partidas registradas.\n");
        return;
    }

    printf("Jugador    | ID Partida | Puntuacion | Movimientos | Resultado\n");
    printf("------------------------------------------------\n");

    while(fread(&partida, sizeof(tPartida), 1, pf) == 1)
    {
        printf("%-10s | %10d | %10d | %11d | %5c\n",
            partida.nombreJugador,
            partida.idPartida,
            partida.puntuacion,
            partida.movimientos,
            partida.resultado);
    }
    pauseEnter();
    system("cls || clear");
    fclose(pf);
}
