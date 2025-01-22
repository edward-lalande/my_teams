/*
** EPITECH PROJECT, 2024
** client
** File description:
** messages
*/

#include <string.h>
#include <stdio.h>

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

static int display_messages(client_t *client)
{
    char *line = NULL;
    char *name = NULL;
    char *content = NULL;
    time_t time = 0;
    size_t len = 0;

    getline(&line, &len, client->server);
    while (!is_code_line(line)) {
        dprintf(1, line);
        name = strtok(line, " ");
        content = strtok(NULL, "[]");
        client_private_message_print_messages(name, time, content);
        getline(&line, &len, client->server);
    }
    dprintf(1, line);
    return EXIT_WITH_SUCCESS;
}

int messages(client_t *client)
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
    display_messages(client);
    return EXIT_WITH_SUCCESS;
}
