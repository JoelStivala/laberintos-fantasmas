#include "servidor_lib.h"
#include "db.h"
#include "Arbol.h"
#include <string.h>

// Inicialización de Winsock
int init_winsock()
{
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

// Creación del socket del servidor
SOCKET create_server_socket()
{
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
        return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    if (listen(s, 1) == SOCKET_ERROR)
    {
        closesocket(s);
        return INVALID_SOCKET;
    }

    printf("Servidor escuchando en puerto %d...\n", PORT);
    return s;
}

// Procesar solicitud (ADDUSER, ADDPARTIDA, GETRANK)
void procesarSolicitudBD(const char *request, char *response)
{
    char comando[32];
    char nombre[64];
    int puntos, movs;
    char resultado;

    tArbol arbolUsuarios;

    inicializarBD(&arbolUsuarios);

    sscanf(request, "%31s\n", comando);

    if (strcmp(comando, "ADDUSER") == 0)
    {
        if (sscanf(request, "ADDUSER %63s", nombre) == 1)
        {
            guardarUsuario(&arbolUsuarios, nombre);
            snprintf(response, BUFFER_SIZE, "Usuario %s guardado correctamente.", nombre);
        }
        else
        {
            snprintf(response, BUFFER_SIZE, "Error: formato incorrecto. Use: ADDUSER <nombre>");
        }
    }
    else if (strcmp(comando, "ADDPARTIDA") == 0)
    {
        if (sscanf(request, "ADDPARTIDA %63s %d %d %c", nombre, &puntos, &movs, &resultado) == 4)
        {
            guardarPartida(nombre, puntos, movs, resultado);
            snprintf(response, BUFFER_SIZE, "Partida de %s registrada correctamente.", nombre);
        }
        else
        {
            snprintf(response, BUFFER_SIZE, "Error: formato incorrecto. Use: ADDPARTIDA <nombre> <puntos> <movs> <resultado>");
        }
    }
    else if (strcmp(comando, "GETRANK") == 0)
    {
        FILE *pf = fopen("../../Files/partidas.dat", "rb");
        tPartida p;
        char linea[128];
        response[0] = '\0';

        if (!pf)
        {
            strcpy(response, "No hay partidas registradas.");
            return;
        }

        strcat(response, "Jugador | ID | Puntos | Movs | Resultado\n");
        strcat(response, "-----------------------------------------\n");

        while (fread(&p, sizeof(tPartida), 1, pf) == 1)
        {
            snprintf(linea, sizeof(linea), "%-10s | %2d | %7d | %4d | %c\n",
                     p.nombreJugador, p.idPartida, p.puntuacion, p.movimientos, p.resultado);
            strcat(response, linea);
        }

        fclose(pf);
    }
    else
    {
        snprintf(response, BUFFER_SIZE, "Comando no reconocido: %s", comando);
    }
}

// Bucle principal del servidor
void run_server()
{
    if (init_winsock() != 0)
    {
        printf("Error al inicializar Winsock.\n");
        return;
    }

    SOCKET server_socket = create_server_socket();
    if (server_socket == INVALID_SOCKET)
    {
        printf("Error al crear socket del servidor.\n");
        WSACleanup();
        return;
    }

    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);

    while (1)
    {
        printf("\nEsperando conexión de cliente...\n");
        SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);

        if (client_socket == INVALID_SOCKET)
        {
            printf("Error en accept().\n");
            continue;
        }

        printf("Cliente conectado.\n");

        char buffer[BUFFER_SIZE];
        char response[BUFFER_SIZE];
        int bytes_received;

        while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0)
        {
            buffer[bytes_received] = '\0';
            printf("Recibido: %s\n", buffer);

            procesarSolicitudBD(buffer, response);
            send(client_socket, response, strlen(response), 0);

            printf("Enviado:  %s\n", response);
        }

        printf("Cliente desconectado.\n");
        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
}
