/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** teams_client
*/

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "commands.h"
#include "client.h"

static char *get_next_token(char *token, unsigned int *count)
{
    if (*count && (*count % 2 != 0)) {
        token = strtok(NULL, "\"\n\r");
        *count = 0;
    }
    *count += 1;
    return token;
}

static char **get_command(char *line)
{
    char **command = malloc(sizeof(char *));
    unsigned int index = 0;
    unsigned int count = 0;
    char *token = NULL;

    for (token = strtok(line, " \n\r"); token; index += 1) {
        command = realloc(command, sizeof(char *) * (index + 2));
        command[index] = strdup(token);
        token = strtok(NULL, "\"\n\r");
        token = get_next_token(token, &count);
    }
    command[index] = NULL;
    return command;
}

static void set_fd(client_t *client)
{
    FD_ZERO(&client->fd);
    FD_SET(client->sock_fd, &client->fd);
    FD_SET(0, &client->fd);
}

static void handle_command(client_t *client)
{
    char *line = NULL;
    size_t len = 0;
    int value = 0;

    getline(&line, &len, client->server);
    while (1) {
        set_fd(client);
        value = select(4, &client->readfds, NULL, NULL, NULL);
        if (value == -1 || getline(&line, &len, stdin) == EOF) {
            client->line = strdup("/logout");
            logout(client);
            break;
        }
        client->line = strdup(line);
        client->command = get_command(line);
        if (search_command(client) == LOGOUT_CODE)
            break;
        free_array(client->command);
        display_prompt();
    }
}

int teams_client(char *ip, char *port)
{
    client_t *client = init_teams_client(port);
    socklen_t serv_len = sizeof(client->serv_addr);

    if (!client) {
        return EXIT_WITH_ERROR;
    }
    if (inet_pton(AF_INET, ip, &client->serv_addr.sin_addr) == ERROR) {
        return EXIT_WITH_ERROR;
    }
    signal(SIGINT, catch_sigint);
    signal(SIGPIPE, catch_sigpipe);
    signal(SIGSEGV, catch_sigsev);
    display_prompt();
    connect(client->sock_fd, (struct sockaddr *)&client->serv_addr, serv_len);
    handle_command(client);
    fclose(client->server);
    return EXIT_WITH_SUCCESS;
}
