/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** unsubscribe
*/

#include <string.h>
#include "command.h"
#include "team.h"
#include "client.h"
#include "server.h"
#include "logging_server.h"

static bool is_in_team(client_t *client, team_t *team)
{
    for (size_t i = 0; i < team->nb_users; i++) {
        if (!strcmp(client->uuid, team->user_uuid[i])) {
            return true;
        }
    }
    return false;
}

static void delete_user(team_t *team, client_t *client)
{
    for (int t = 0; t < team->nb_users; t++) {
        if (!strcmp(client->name, team->user_name[t])) {
            memset(team->user_name[t], '\0', NAME_LENGTH);
            memset(team->user_uuid[t], '\0', NAME_LENGTH);
            team->nb_users -= 1;
        }
    }
}

int check_primary_error_unsub(client_t *client, char **args)
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
    return SUCCES;
}

int command_unsubscribe(COMMAND_ARGUMENTS)
{
    int index = 0;
    team_t *team = NULL;

    if (check_primary_error_unsub(client, args) == ERROR) {
        return ERROR;
    }
    team = get_team(server, args[1]);
    if (!team) {
        return send_message(207, RED, client);
    }
    if (is_in_team(client, team) == true) {
        delete_user(team, client);
        server_event_user_unsubscribed(args[1], client->uuid);
        save_server(server);
        return send_message(101, GREEN, client);
    }
    return send_message(212, RED, client);
}
