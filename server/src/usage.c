/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** print_usage
*/

#include <stdio.h>

#include "server.h"

int usage(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("\tport is the port number on which the server socket listens.\n");
    return SUCCES;
}
