/*
** EPITECH PROJECT, 2024
** client
** File description:
** exit_cli
*/

#include <stdlib.h>
#include "commands.h"

int exit_cli(client_t *client)
{
    (void)client;
    exit(0);
    return EXIT_COMMAND_BUILT_IN;
}
