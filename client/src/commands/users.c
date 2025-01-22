/*
** EPITECH PROJECT, 2024
** client
** File description:
** users
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "client.h"
#include "commands.h"
#include "logging_client.h"

static bool is_code_line(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == ']') {
            return false;
        }
    }
    return true;
}

static int display_user(char *line)
{
    char *token = NULL;
    char *state = NULL;
    char *uuid = NULL;

    token = strtok(line, " ");
    uuid = strtok(NULL, "[]");
    state = strtok(NULL, " ");
    client_print_users(uuid, token, atoi(state));
    return EXIT_WITH_SUCCESS;
}

static int display_users(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, client->server);
    while (!is_code_line(line)) {
        dprintf(1, line);
        display_user(line);
        getline(&line, &len, client->server);
    }
    dprintf(1, line);
    return EXIT_WITH_SUCCESS;
}

int users(client_t *client)
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
    return display_users(client);
}
