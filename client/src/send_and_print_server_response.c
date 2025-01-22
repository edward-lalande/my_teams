/*
** EPITECH PROJECT, 2024
** client
** File description:
** get_server_response
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

int get_code(char *line)
{
    return atoi(line + 7);
}

void send_and_print_server_response(client_t *client, char *buffer)
{
    char *str = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, buffer);
    getline(&str, &len, fdopen(client->sock_fd, "r"));
    dprintf(1, "%s\033[0m", str);
    if (atoi(str) < BEGIN_OF_ERROR_CODE) {
        getline(&str, &len, fdopen(client->sock_fd, "r"));
        dprintf(1, str);
    }
}
