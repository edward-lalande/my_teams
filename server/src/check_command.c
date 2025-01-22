/*
** EPITECH PROJECT, 2024
** server
** File description:
** check_command
*/

#include <errno.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "command.h"

static char *get_next_token(char *token, int *count)
{
    if (*count && (*count % 2 != 0)) {
        token = strtok(NULL, "\"\n\r");
        *count = 0;
    }
    *count += 1;
    return token;
}

static char **get_command(server_t *server, client_t *client)
{
    char buffer[MAX_SIZE];
    const ssize_t value = read(client->socket_fd, buffer, MAX_SIZE);
    char **command = malloc(sizeof(char *));
    unsigned int index = 0;
    unsigned int count = 0;
    char *token = NULL;

    if (value == SYSERR || !command) {
        error(ERROR, errno, strerror(errno));
    }
    buffer[value] = '\0';
    for (token = strtok(buffer, " \n\r"); token; index += 1) {
        command = realloc(command, sizeof(char *) * (index + 2));
        command[index] = strdup(token);
        token = strtok(NULL, "\"\n\r");
        token = get_next_token(token, &count);
    }
    command[index] = NULL;
    return command;
}

static void handle_command(server_t *server, client_t *client)
{
    char **command = get_command(server, client);
    bool is_passed = false;

    for (unsigned int i = 0; i < NB_COMMANDS; i++) {
        if (command[0] && !strcmp(command[0], commands[i].command)) {
            commands[i].function(client, server, command);
            is_passed = true;
            break;
        }
    }
    if (!is_passed && command[0]) {
        send_message(200, RED, client);
    }
    for (unsigned int i = 0; command[i]; i++) {
        free(command[i]);
    }
    free(command);
}

int check_command(server_t *server)
{
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!server->clients[i].socket_fd) {
            continue;
        }
        if (FD_ISSET(server->clients[i].socket_fd, &server->readfs)) {
            handle_command(server, &server->clients[i]);
        }
    }
}
