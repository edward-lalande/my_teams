/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_server
*/

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "server.h"
#include "logging_server.h"

static void get_clients(server_t *server)
{
    const int fd = open(SAVE_CLIENTS, O_RDONLY);
    client_t *client = NULL;

    if (fd != SYSERR) {
        if (read(fd, server->clients, sizeof(server->clients)) == SYSERR) {
            error(ERROR, errno, strerror(errno));
        }
        close(fd);
    }
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        client = &server->clients[i];
        if (client->state != DEFAULT) {
            server_event_user_loaded(client->uuid, client->name);
        }
        client->socket_fd = 0;
        if (client->state == LOGIN) {
            client->state = LOGOUT;
        }
    }
}

static void get_teams(server_t *server)
{
    const int fd = open(SAVE_TEAMS, O_RDONLY);

    if (fd != SYSERR) {
        if (read(fd, server->teams, sizeof(server->teams)) == SYSERR) {
            error(ERROR, errno, strerror(errno));
        }
        close(fd);
    }
}

static server_t *init_server(const int port)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        error(ERROR, errno, strerror(errno));
    }
    server->port = port;
    server->address.sin_family = AF_INET;
    server->address.sin_port = htons(port);
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->socket_fd) {
        error(ERROR, errno, strerror(errno));
    }
    return server;
}

server_t *get_server(const int port)
{
    server_t *server = init_server(port);
    struct sockaddr *address = (struct sockaddr *)&server->address;

    if (bind(server->socket_fd, address, sizeof(server->address)) == SYSERR) {
        error(ERROR, errno, strerror(errno));
    }
    get_clients(server);
    get_teams(server);
    return server;
}
