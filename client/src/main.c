/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** main
*/

#include <string.h>
#include <stdio.h>

#include "client.h"

int main(int ac, char **av)
{
    if (ac < NB_ARGS_REQUIRED) {
        print_usage();
        return EXIT_WITH_SUCCESS;
    }
    return teams_client(av[IP], av[PORT]);
}
