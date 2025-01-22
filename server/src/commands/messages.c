/*
** EPITECH PROJECT, 2024
** server
** File description:
** messages
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"
#include "server.h"

static int user_exist(server_t *server, char *uuid)
{
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, uuid)) {
            return SUCCES;
        }
    }
    return ERROR;
}

static int check_messages_errors(COMMAND_ARGUMENTS)
{
    if (arraylen(args) < 2) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 2) {
        return send_message(202, RED, client);
    }
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (user_exist(server, args[1]) == ERROR) {
        return send_message(205, RED, client);
    }
    return SUCCES;
}

static char *get_name_by_uuid(server_t *server, char *uuid)
{
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, uuid)) {
            return server->clients[i].name;
        }
    }
    return "";
}

static int show_message(server_t *server, client_t *client, message_t message)
{
    const char *name = get_name_by_uuid(server, message.sender);
    time_t time = 0;

    if (!strcmp(message.content, "")) {
        return ERROR;
    }
    if (!strcmp(message.sender, client->uuid)) {
        dprintf(client->socket_fd, "%s [%s] %d\n", name,
        message.content, time);
    } else {
        dprintf(client->socket_fd, "%s [%s] %d\n", name,
        message.content, time);
    }
    return SUCCES;
}

int command_messages(COMMAND_ARGUMENTS)
{
    discussion_t *discussion = NULL;

    if (check_messages_errors(client, server, args) == ERROR) {
        return ERROR;
    }
    for (unsigned int i = 0; i < MAX_DISCUSSION; i++) {
        if (!strcmp(client->discussions[i].user, args[1])) {
            discussion = &server->clients->discussions[i];
        }
    }
    send_message(101, GREEN, client);
    for (unsigned int i = 0; discussion && i < MAX_MESSAGE; i++) {
        show_message(server, client, discussion->messages[i]);
    }
    send_message(101, GREEN, client);
    return SUCCES;
}
