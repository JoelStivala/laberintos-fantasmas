#include "../Headers/juego.h"

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

void draw(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int i, j, k;
    int hayFantasma;
    tFantasma* fantasma;

    for(i = 0 ; i < laberinto->cf ; i++)
    {
        for(j = 0 ; j < laberinto->cc ; j++)
        {
            if(i == jugador->posY && j == jugador->posX)
                printf("%c", jugador->j);
            else
            {
                hayFantasma = 0;
                for(k = 0 ; k < fantasmas->ce ; k++)
                {
                    fantasma = (tFantasma*)((char*)fantasmas->v + k * fantasmas->tamElem);

                    if(fantasma->posY == i && fantasma->posX == j)
                    {
                        printf("F");
                        hayFantasma = 1;
                        break;
                    }
                }
                if(!hayFantasma)
                    printf("%c", laberinto->mat[i][j]);
            }
        }
        puts("");
    }
}


void procesarCelda(tJugador* jugador, tVector* fantasmas, char* celda)
{
    int i;
    tFantasma* fantasma;

    for(i = 0 ; i < fantasmas->ce ; i++)
    {
        fantasma = (tFantasma*)((char*)fantasmas->v + i * fantasmas->tamElem);
        if(jugador->posX == fantasma->posX && jugador->posY == fantasma->posY)
        {
            jugador->vidas--;
            vectorEliminarPosicion(fantasmas, i);
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

void inicializarJuego(tConfig* config, tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int xIni, yIni;

    inicializarConfiguracion(config);
    inicializarLaberinto(laberinto, &xIni, &yIni, config);
    inicializarJugador(jugador, xIni, yIni, config);
    //inicializarFantasmas(fantasmas, config);
    vectorCrear(fantasmas, sizeof(tFantasma), config->maxNumeroFantasmas);



    cargarPosicionesFantasmas(fantasmas, laberinto);
    eliminarFantasmasLaberinto(laberinto);
}

void gameLoop(tLaberinto* laberinto, tJugador* jugador, tVector* fantasmas)
{
    int nuevoX, nuevoY;
    char input;
    char buffer[10];
    //tCola cola;
    tFantasma* fantasma;

    //colaCrear(&cola);

    while(jugador->vidas > 0 && laberinto->mat[jugador->posY][jugador->posX] != 'S')
    {
        system("cls");
        draw(laberinto, jugador, fantasmas);
        printf("VIDAS: %d\nPUNTOS: %d\n", jugador->vidas, jugador->puntos);

        input = getch();
        //colaEncolar(&cola, &input, sizeof(input));
        calcularNuevaPosicion(jugador, input, &nuevoX, &nuevoY);

        if(!hayBloque(laberinto, nuevoX, nuevoY))
        {
            registrarDireccion(jugador, input);
            mover(jugador, nuevoX, nuevoY);
        }
        for(int i = 0 ; i < fantasmas->ce ; i++)
        {
            fantasma = (tFantasma*)((char*)fantasmas->v + i * fantasmas->tamElem);
            moverFantasmas(fantasma, jugador, laberinto);
        }
        procesarCelda(jugador, fantasmas, &laberinto->mat[jugador->posY][jugador->posX]);
    }

    system("cls");
    if(jugador->vidas > 0)
    {
        puts("Has ganado!\n");
    }
    else
    {
        puts("Game Over\n");
    }

    printf("Lista de movimientos: ");
    while(!colaVacia(&jugador->colaMovimientos))
    {
        colaQuitar(&jugador->colaMovimientos, buffer, sizeof(buffer));
        printf("%s", buffer);
    }

    puts("");
    system("pause");
    colaVaciar(&jugador->colaMovimientos);
}
