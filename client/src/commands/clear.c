/*
** EPITECH PROJECT, 2024
** client
** File description:
** clear
*/

#include <stdlib.h>
#include "client.h"
#include "commands.h"

int clear(client_t *client)
{
    (void)client;
    system("clear");
    return EXIT_COMMAND_BUILT_IN;
}
