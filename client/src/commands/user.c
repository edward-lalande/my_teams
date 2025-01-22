/*
** EPITECH PROJECT, 2024
** client
** File description:
** user
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logging_client.h"
#include "client.h"

static int display_user(client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    char *state = NULL;

    getline(&line, &len, client->server);
    dprintf(1, line);
    token = strtok(line, " ");
    state = strtok(NULL, " ");
    state = strtok(NULL, " ");
    client_print_user(client->command[1], token, atoi(state));
    return EXIT_WITH_SUCCESS;
}

int user(client_t *client)
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
    if (get_code(line) == 205) {
        client_error_unknown_user(client->command[1]);
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    return display_user(client);
}
