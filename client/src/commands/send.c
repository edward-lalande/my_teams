/*
** EPITECH PROJECT, 2024
** client
** File description:
** send
*/

#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "logging_client.h"

int send_command(client_t *client)
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
    client_event_private_message_received(client->uuid, client->command[2]);
    return EXIT_WITH_SUCCESS;
}
