/*
** EPITECH PROJECT, 2024
** server
** File description:
** close_server
*/

#include <errno.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "server.h"
#include "command.h"

int close_server(server_t *server)
{
    char **command = malloc(sizeof(char *) * 2);

    if (!command) {
        return ERROR;
    }
    command[0] = strdup("/logout");
    command[1] = NULL;
    for (int i = 0; command[0] && i < SOMAXCONN; i++) {
        if (server->clients[i].state == LOGIN) {
            command_logout(&server->clients[i], server, command);
        }
    }
    if (close(server->socket_fd) == SYSERR) {
        error(ERROR, errno, strerror(errno));
    }
    if (command[0]) {
        free(command[0]);
    }
    free(command);
    return SUCCES;
}
