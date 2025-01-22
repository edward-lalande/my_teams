/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** init_teams_client
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

client_t *init_teams_client(char *port)
{
    client_t *client = malloc(sizeof(client_t));
    const int options = SO_REUSEADDR | SO_REUSEPORT;

    client->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sock_fd == ERROR) {
        return NULL;
    }
    setsockopt(client->sock_fd, SOL_SOCKET, options, NULL, 0);
    client->serv_addr.sin_family = AF_INET;
    FD_SET(0, &client->readfds);
    client->serv_addr.sin_port = htons(atoi(port));
    client->command = NULL;
    client->line = NULL;
    client->server = fdopen(client->sock_fd, "r");
    if (!client->server) {
        return NULL;
    }
    return client;
}
