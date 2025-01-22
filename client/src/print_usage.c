/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** print_usage
*/

#include <stdio.h>
#include "client.h"

void print_usage(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\t  ip:\tis the server ip address");
    printf(" on which the server socket listens\n");
    printf("\t  port:\tis the port number on which ");
    printf("the server socket listens\n");
}
