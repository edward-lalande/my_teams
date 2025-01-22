/*
** EPITECH PROJECT, 2024
** client
** File description:
** login
*/

#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "logging_client.h"

static int set_login(client_t *client, char *line)
{
    char *token = NULL;

    strcpy(client->name, client->command[1]);
    token = strtok(line, " \n");
    token = strtok(NULL, " \n");
    strcpy(client->uuid, token);
    client_event_logged_in(client->uuid, client->name);
    client->is_connected = true;
    return EXIT_WITH_SUCCESS;
}

int login(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, client->line);
    getline(&line, &len, client->server);
    dprintf(1, line);
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    getline(&line, &len, client->server);
    return set_login(client, line);
}
