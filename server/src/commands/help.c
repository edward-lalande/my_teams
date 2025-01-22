/*
** EPITECH PROJECT, 2024
** server
** File description:
** help
*/

#include <stdio.h>

#include "command.h"

int command_help(COMMAND_ARGUMENTS)
{
    if (arraylen(args) > 1) {
        return send_message(202, RED, client);
    }
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "This is a help message that is not ");
    dprintf(client->socket_fd, "widely used but it remains a help message.\n");
    return SUCCES;
}
