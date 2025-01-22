/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#include "server.h"

#include <errno.h>
#include <error.h>
#include <string.h>

int server(const int port)
{
    server_t *server = get_server(port);

    listen_server(server);
    return close_server(server);
}
