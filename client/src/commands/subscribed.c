/*
** EPITECH PROJECT, 2024
** client
** File description:
** subscribed
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void display_teams(client_t *client)
{
    char *line = NULL;
    char *uuid = NULL;
    char *name = NULL;
    char *description = NULL;
    size_t len = 0;

    getline(&line, &len, client->server);
    while (!is_code_line(line)) {
        dprintf(1, line);
        uuid = strtok(line, "[]");
        name = strtok(NULL, " []");
        description = strtok(NULL, "[]");
        client_print_teams(uuid, name, description);
        getline(&line, &len, client->server);
    }
    dprintf(1, line);
}

static void display_users(client_t *client)
{
    char *line = NULL;
    char *uuid = NULL;
    char *name = NULL;
    char *state = NULL;
    size_t len = 0;

    getline(&line, &len, client->server);
    while (!is_code_line(line)) {
        dprintf(1, line);
        name = strtok(line, "[]");
        uuid = strtok(NULL, " []");
        state = strtok(NULL, " \n");
        client_print_users(uuid, name, atoi(state));
        getline(&line, &len, client->server);
    }
    dprintf(1, line);
}

static int manage_subscribed(client_t *client)
{
    if (arrlen(client->command) == 1) {
        display_teams(client);
    } else {
        display_users(client);
    }
    return EXIT_SUCCESS;
}

int subscribed(client_t *client)
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
    return manage_subscribed(client);
}
