/*
** EPITECH PROJECT, 2024
** client
** File description:
** logout
*/

#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "logging_client.h"

int logout(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, client->line);
    getline(&line, &len, client->server);
    dprintf(1, line);
    if (!client->is_connected) {
        client_error_unauthorized();
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    client->is_connected = false;
    client_event_logged_out(client->uuid, client->name);
    return LOGOUT_CODE;
}
