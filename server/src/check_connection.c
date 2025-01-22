/*
** EPITECH PROJECT, 2024
** server
** File description:
** check_connection
*/

#include <errno.h>
#include <error.h>
#include <string.h>

#include "server.h"

static client_t create_client(const int socket)
{
    client_t client = {0};

    client.socket_fd = socket;
    client.state = DEFAULT;
    return client;
}

static void accept_client(server_t *server)
{
    struct sockaddr_in addr = {0};
    socklen_t addrlen = sizeof(addr);
    int client = accept(server->socket_fd, (struct sockaddr *)&addr, &addrlen);

    if (client == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (server->clients[i].state == DEFAULT) {
            server->clients[i] = create_client(client);
            send_message(100, GREEN, &server->clients[i]);
            display_message("Un nouvel utilisateur est connecté!", GREEN);
            break;
        }
    }
}

void check_connection(server_t *server)
{
    const int max_sd = server->max_sd + 1;

    if (select(max_sd, &server->readfs, NULL, NULL, &server->time) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (FD_ISSET(server->socket_fd, &server->readfs)) {
        accept_client(server);
    }
}
