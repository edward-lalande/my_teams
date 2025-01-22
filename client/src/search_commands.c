/*
** EPITECH PROJECT, 2024
** client
** File description:
** search_commands
*/

#include <string.h>
#include <stdio.h>
#include "commands.h"
#include "client.h"

int search_command(client_t *client)
{
    if (!client->command || !client->command[0]) {
        return EXIT_WITH_ERROR;
    }
    for (size_t i = 0; cmd[i].command != NULL; ++i) {
        if (!strcmp(cmd[i].command, client->command[COMMAND_INDEX])) {
            return cmd[i].func(client);
        }
    }
    return EXIT_WITH_SUCCESS;
}
