/*
** EPITECH PROJECT, 2024
** server
** File description:
** send
*/

#include <string.h>
#include <stdbool.h>

#include "command.h"
#include "logging_server.h"

static int check_send_errors(COMMAND_ARGUMENTS)
{
    if (arraylen(args) < 3) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 3) {
        return send_message(202, RED, client);
    }
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (strlen(args[2]) > BODY_LENGTH) {
        return send_message(202, RED, client);
    }
    return SUCCES;
}

static int add_message(discussion_t *discussion, char *sender, char *content)
{
    for (unsigned int i = 0; i < MAX_MESSAGE; i++) {
        if (!strcmp(discussion->messages[i].sender, "")) {
            strcpy(discussion->messages[i].sender, sender);
            strcpy(discussion->messages[i].content, content);
            return SUCCES;
        }
    }
    return ERROR;
}

static int send_to_client(client_t *client, char *uuid, char *content)
{
    discussion_t *discussion = NULL;

    for (unsigned int i = 0; i < MAX_DISCUSSION; i++) {
        if (!strcmp(client->discussions[i].user, uuid)) {
            discussion = &client->discussions[i];
        }
    }
    for (unsigned int i = 0; !discussion && i < MAX_DISCUSSION; i++) {
        if (!strcmp(client->discussions[i].user, "")) {
            strcpy(client->discussions[i].user, uuid);
            discussion = &client->discussions[i];
        }
    }
    if (!discussion) {
        return ERROR;
    }
    if (add_message(discussion, client->uuid, content) == ERROR) {
        return ERROR;
    }
    return SUCCES;
}

static int send_to_other_client(client_t *client, char *uuid, char *content)
{
    discussion_t *discussion = NULL;

    for (unsigned int i = 0; i < MAX_DISCUSSION; i++) {
        if (!strcmp(client->discussions[i].user, uuid)) {
            discussion = &client->discussions[i];
        }
    }
    for (unsigned int i = 0; !discussion && i < MAX_DISCUSSION; i++) {
        if (!strcmp(client->discussions[i].user, "")) {
            strcpy(client->discussions[i].user, uuid);
            discussion = &client->discussions[i];
        }
    }
    if (!discussion) {
        return ERROR;
    }
    if (add_message(discussion, uuid, content) == ERROR) {
        return ERROR;
    }
    return SUCCES;
}

static int send_to_both_client(client_t *client, client_t *other, char **args)
{
    if (send_to_client(client, args[1], args[2]) == ERROR) {
        return send_message(400, RED, client);
    }
    if (send_to_other_client(other, client->uuid, args[2]) == ERROR) {
        return send_message(400, RED, client);
    }
    return SUCCES;
}

int command_send(COMMAND_ARGUMENTS)
{
    client_t *other = NULL;

    if (check_send_errors(client, server, args) == ERROR) {
        return ERROR;
    }
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, args[1])) {
            other = &server->clients[i];
        }
    }
    if (!other) {
        return send_message(205, RED, client);
    }
    if (send_to_both_client(client, other, args) == ERROR) {
        return ERROR;
    }
    save_server(server);
    server_event_private_message_sended(client->uuid, other->uuid, args[2]);
    return send_message(101, GREEN, client);
}
