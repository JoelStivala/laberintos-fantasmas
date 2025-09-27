#include "juego.h"

int mostrarMenu()
{
    int opcion;

    puts("======LABERINTOS Y FANTASMAS======");
    puts("1) Jugar");
    puts("2) Ver tabla de puntuaciones");
    puts("3) Salir");

    scanf("%d", &opcion);

    return opcion;
}

void draw(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas)
{
    int i, j, k;
    int hayFantasma;

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            if(i == jugador->posY && j == jugador->posX)
                printf("%c", jugador->j);
            else
            {
                hayFantasma = 0;
                for(k = 0 ; k < fantasmas->cntFantasmas ; k++)
                {
                    if(fantasmas->f[k].posY == i && fantasmas->f[k].posX == j)
                    {
                        printf("%c", fantasmas->i);
                        hayFantasma = 1;
                        break; //reemplazar por un while luego
                    }
                }
                if(!hayFantasma)
                    printf("%c", laberinto->mat[i][j]);
            }

        }
        puts("");
    }
}

void procesarCelda(tJugador* jugador, vFantasmas* fantasmas, char* celda)
{
    int i;

    for(i = 0 ; i < fantasmas->cntFantasmas ; i++)
    {
        if(jugador->posX == fantasmas->f[i].posX && jugador->posY == fantasmas->f[i].posY)
        {
            jugador->vidas--;
            eliminarFantasmasPosicion(fantasmas, i);
        }
    }

    if (*celda == 'P')
    {
        jugador->puntos++;
        *celda = '.';
    }
    else if (*celda == 'V')
    {
        jugador->vidas++;
        *celda = '.';
    }
}

void inicializarJuego(tConfig* config, tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas)
{
    inicializarConfiguracion(config);
    inicializarLaberinto(laberinto, config);
    inicializarJugador(jugador, config);
    inicializarFantasmas(fantasmas, config);

    cargarPosicionesFantasmas(fantasmas, laberinto);
    eliminarFantasmasLaberinto(laberinto);
}

void gameLoop(tLaberinto* laberinto, tJugador* jugador, vFantasmas* fantasmas)
{
    int nuevoX, nuevoY;
    char input;

    while(jugador->vidas > 0 && laberinto->mat[jugador->posY][jugador->posX] != 'S')
    {
        system("cls");
        draw(laberinto, jugador, fantasmas);
        printf("VIDAS: %d\nPUNTOS: %d\n", jugador->vidas, jugador->puntos);

        input = getch();
        calcularNuevaPosicion(jugador, input, &nuevoX, &nuevoY);

        if(!hayBloque(laberinto, nuevoX, nuevoY))
        {
            mover(jugador, nuevoX, nuevoY);
            procesarCelda(jugador, fantasmas, &laberinto->mat[jugador->posY][jugador->posX]);
        }

        for(int i = 0 ; i < fantasmas->cntFantasmas ; i++)
            moverFantasmas(&fantasmas->f[i], jugador, laberinto);
    }

    system("cls");
    puts("Game Over");
    pauseEnter();
}
