/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** subscribe
*/

#include <string.h>
#include <stdio.h>

#include "server.h"
#include "command.h"
#include "logging_server.h"

static int is_team_exists(server_t *server, char const *uuid)
{
    for (int i = 0; i < MAX_TEAM; i++) {
        if (!strcmp(server->teams[i].uuid, uuid)) {
            return i;
        }
    }
    return ERROR;
}

static bool is_in_team(client_t *client, team_t *team, char **args)
{
    for (size_t i = 0; i < team->nb_users; i++) {
        if (!strcmp(client->uuid, team->user_uuid[i])) {
            return true;
        }
    }
    return false;
}

static int check_error_subscribe(COMMAND_ARGUMENTS, team_t *team)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (arraylen(args) < 2) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 2) {
        return send_message(202, RED, client);
    }
    if (is_team_exists(server, args[1]) == ERROR) {
        return send_message(207, RED, client);
    }
    if (is_in_team(client, team, args) == true) {
        return send_message(211, RED, client);
    }
    if (server->teams->nb_users >= MAX_USERS_TEAM) {
        return send_message(210, RED, client);
    }
    return SUCCES;
}

int command_subscribe(COMMAND_ARGUMENTS)
{
    int index = 0;
    team_t *team = NULL;

    if (check_error_subscribe(client, server, args, team) == ERROR) {
        return ERROR;
    }
    if (!team) {
        return send_message(207, RED, client);
    }
    team = get_team(server, args[1]);
    strcpy(team->user_uuid[team->nb_users], client->uuid);
    strcpy(team->user_name[team->nb_users], client->name);
    team->nb_users += 1;
    server_event_user_subscribed(args[1], client->uuid);
    save_server(server);
    send_message(101, GREEN, client);
    return SUCCES;
}
