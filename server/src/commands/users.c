/*
** EPITECH PROJECT, 2024
** server
** File description:
** users
*/

#include <stdio.h>

#include "command.h"

int command_users(COMMAND_ARGUMENTS)
{
    if (arraylen(args) > 1) {
        return send_message(202, RED, client);
    }
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    send_message(101, GREEN, client);
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (server->clients[i].state != DEFAULT) {
            dprintf(client->socket_fd, server->clients[i].name);
            dprintf(client->socket_fd, " [%s]", server->clients[i].uuid);
            dprintf(client->socket_fd, " %d\n", server->clients[i].state - 1);
        }
    }
    send_message(101, GREEN, client);
    return SUCCES;
}
