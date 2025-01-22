/*
** EPITECH PROJECT, 2024
** sub create
** File description:
** My teams Proj
*/

#include <stdio.h>
#include <string.h>

#include "command.h"

void sub_create_team(team_t *team, char **args)
{
    strcpy(team->name, args[1]);
    strcpy(team->description, args[2]);
    uuid_generate(team->binuuid);
    uuid_unparse(team->binuuid, team->uuid);
}

int check_channel_error(COMMAND_ARGUMENTS)
{
    if (check_not_found(server, client, 1) == ERROR) {
        return ERROR;
    }
    if (check_create_error(client, args, DESCRIPTION_LENGTH) == ERROR) {
        return ERROR;
    }
    return SUCCES;
}

int check_thread_error(COMMAND_ARGUMENTS)
{
    if (check_not_found(server, client, 2) == ERROR) {
        return ERROR;
    }
    if (check_create_error(client, args, BODY_LENGTH) == ERROR) {
        return ERROR;
    }
    return SUCCES;
}

int check_error_reply(COMMAND_ARGUMENTS)
{
    if (check_not_found(server, client, 3) == ERROR) {
        return ERROR;
    }
    if (arraylen(args) < 2) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 2 || strlen(args[1]) > BODY_LENGTH) {
        return send_message(202, RED, client);
    }
    return SUCCES;
}
