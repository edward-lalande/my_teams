/*
** EPITECH PROJECT, 2024
** server
** File description:
** set_clients
*/

#include "server.h"

static int set_all_clients(server_t *server)
{
    int max_sd = server->socket_fd;

    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!server->clients[i].socket_fd) {
            continue;
        }
        FD_SET(server->clients[i].socket_fd, &server->readfs);
        if (server->clients[i].socket_fd > max_sd) {
            max_sd = server->clients[i].socket_fd;
        }
    }
    return max_sd;
}

void set_clients(server_t *server)
{
    FD_ZERO(&server->readfs);
    FD_SET(server->socket_fd, &server->readfs);
    server->max_sd = set_all_clients(server);
}
