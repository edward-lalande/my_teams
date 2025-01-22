/*
** EPITECH PROJECT, 2024
** server
** File description:
** logout
*/

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "logging_server.h"

int command_logout(COMMAND_ARGUMENTS)
{
    if (arraylen(args) > 1) {
        return send_message(202, RED, client);
    }
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "Uuid: %s\n", client->uuid);
    if (close(client->socket_fd) == ERROR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (client->state == LOGIN) {
        client->state = LOGOUT;
        server_event_user_logged_out(client->uuid);
    }
    client->socket_fd = 0;
    return SUCCES;
}
