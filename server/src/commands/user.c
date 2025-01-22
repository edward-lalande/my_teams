/*
** EPITECH PROJECT, 2024
** server
** File description:
** user
*/

#include <stdio.h>
#include <string.h>

#include "command.h"

static int check_login_errors(COMMAND_ARGUMENTS)
{
    if (arraylen(args) < 2) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 2) {
        return send_message(202, RED, client);
    }
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    return SUCCES;
}

int command_user(COMMAND_ARGUMENTS)
{
    if (check_login_errors(client, server, args) == ERROR) {
        return ERROR;
    }
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, args[1])) {
            send_message(101, GREEN, client);
            dprintf(client->socket_fd, server->clients[i].name);
            dprintf(client->socket_fd, " [%s] ", server->clients[i].uuid);
            dprintf(client->socket_fd, "%d\n", server->clients[i].state - 1);
            return SUCCES;
        }
    }
    return send_message(205, RED, client);
}
