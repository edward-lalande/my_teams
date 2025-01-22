/*
** EPITECH PROJECT, 2024
** client
** File description:
** subscribe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "commands.h"
#include "logging_client.h"

int subscribe(client_t *client)
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
    if (get_code(line) == 207) {
        client_error_unknown_team(client->command[1]);
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    client_print_subscribed(client->uuid, client->command[1]);
    return EXIT_SUCCESS;
}
