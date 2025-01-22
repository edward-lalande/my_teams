/*
** EPITECH PROJECT, 2024
** server
** File description:
** use
*/

#include <stdio.h>
#include <string.h>

#include "command.h"

static int set_team(COMMAND_ARGUMENTS)
{
    strcpy(client->team_context, args[1]);
    memset(client->channel_context, 0, UUID_LENGTH);
    memset(client->thread_context, 0, UUID_LENGTH);
    return SUCCES;
}

static int set_channel(COMMAND_ARGUMENTS)
{
    strcpy(client->channel_context, args[2]);
    memset(client->thread_context, 0, UUID_LENGTH);
    return SUCCES;
}

static int set_thread(COMMAND_ARGUMENTS)
{
    strcpy(client->thread_context, args[3]);
    return SUCCES;
}

static int check_user_error(client_t *client, char **args)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (arraylen(args) > 4) {
        return send_message(202, RED, client);
    }
    if (arraylen(args) == 1) {
        memset(client->team_context, 0, UUID_LENGTH);
        memset(client->channel_context, 0, UUID_LENGTH);
        memset(client->thread_context, 0, UUID_LENGTH);
    }
    return SUCCES;
}

int command_use(COMMAND_ARGUMENTS)
{
    if (check_user_error(client, args) == ERROR) {
        return ERROR;
    }
    if (arraylen(args) > 1 && set_team(client, server, args) == ERROR) {
        return ERROR;
    }
    if (arraylen(args) > 2 && set_channel(client, server, args) == ERROR) {
        return ERROR;
    }
    if (arraylen(args) == 4 && set_thread(client, server, args) == ERROR) {
        return ERROR;
    }
    return send_message(101, GREEN, client);
}
