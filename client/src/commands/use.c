/*
** EPITECH PROJECT, 2024
** use
** File description:
** use client teams
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "logging_client.h"
#include "client.h"

static void fill_context_uuid(client_t *client)
{
    if (arrlen(client->command) >= 2) {
        strcpy(client->team_context, client->command[1]);
    }
    if (arrlen(client->command) >= 3) {
        strcpy(client->channel_context, client->command[2]);
    }
    if (arrlen(client->command) == 4) {
        strcpy(client->thread_context, client->command[3]);
    }
}

int use(client_t *client)
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
    if (get_code(line) == 202) {
        return EXIT_WITH_ERROR;
    }
    memset(client->team_context, 0, UUID_LENGTH);
    memset(client->channel_context, 0, UUID_LENGTH);
    memset(client->thread_context, 0, UUID_LENGTH);
    fill_context_uuid(client);
    return EXIT_WITH_SUCCESS;
}
