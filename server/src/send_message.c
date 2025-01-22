/*
** EPITECH PROJECT, 2024
** server
** File description:
** send_message
*/

#include <stdio.h>

#include "client.h"
#include "message.h"

int send_message(const int code, const int color, const client_t *client)
{
    const int socket = client->socket_fd;

    for (unsigned int i = 0; i < NB_MESSAGES; i++) {
        if (messages[i].code == code) {
            dprintf(socket, "\033[0;%dm", color);
            dprintf(socket, "%d: %s\033[0m\n", code, messages[i].message);
        }
    }
    if (color == RED) {
        return ERROR;
    }
    return SUCCES;
}
