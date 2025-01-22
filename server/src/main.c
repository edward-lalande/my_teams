/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** main
*/

#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"

int main(int ac, char **av)
{
    if (ac == NB_ARGS_REQUIRED && !strcmp(av[1], "-h")) {
        return usage();
    }
    if (ac != NB_ARGS_REQUIRED || atoi(av[1]) == 0) {
        error(ERROR, ERROR, "Invalid arguments. Use -h.");
    }
    return server(atoi(av[1]));
}
