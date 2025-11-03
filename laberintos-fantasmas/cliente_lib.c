#include "cliente_lib.h"
#include <stdio.h>
#include <string.h>

int init_winsock() {
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
}

SOCKET connect_to_server(const char *server_ip, int port) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return INVALID_SOCKET;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        closesocket(sock);
        return INVALID_SOCKET;
    }

    return sock;
}

int send_request(SOCKET sock, const char *request, char *response) {
    if (send(sock, request, strlen(request), 0) < 0) {
        return -1;
    }

    int bytes_received = recv(sock, response, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        return -1;
    }

    response[bytes_received] = '\0';
    return 0;
}

void close_connection(SOCKET sock) {
    closesocket(sock);
    WSACleanup();
}

int enviarUsuarioAlServidor(SOCKET sock, const char *nombreUsuario)
{
    char request[BUFFER_SIZE], response[BUFFER_SIZE];
    snprintf(request, sizeof(request), "ADDUSER %s\n", nombreUsuario);

    if (send_request(sock, request, response) == 0)
        printf("Servidor: %s\n", response);
    else
        printf("Error enviando usuario.\n");

    return 0;
}

int enviarPartidaAlServidor(SOCKET sock, const char *nombreJugador, int puntuacion, int movimientos, char resultado)
{

    char request[BUFFER_SIZE], response[BUFFER_SIZE];
    snprintf(request, sizeof(request), "ADDPARTIDA %s %d %d %c\n", nombreJugador, puntuacion, movimientos, resultado);

    if (send_request(sock, request, response) == 0)
        printf("Servidor: %s\n", response);
    else
        printf("Error enviando partida.\n");

    return 0;
}

int solicitarRankingAlServidor(SOCKET sock)
{
    system("cls || clear");
    char request[BUFFER_SIZE] = "GETRANK\n";
    char response[BUFFER_SIZE];

    if (send_request(sock, request, response) == 0)
        printf("\n=== RANKING ===\n%s\n", response);
    else
        printf("Error solicitando ranking.\n");

    return 0;
}
