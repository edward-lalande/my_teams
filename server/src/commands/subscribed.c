/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** subscribed
*/

#include <string.h>
#include <stdio.h>

#include "server.h"
#include "command.h"
#include "logging_server.h"

static int get_state_by_uuid(server_t *server, char *uuid)
{
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, uuid)) {
            return server->clients[i].state - 1;
        }
    }
    return 0;
}

static void list_subscribed_members(server_t *server, client_t *client,
    team_t *team)
{
    for (int t = 0; t < team->nb_users; t++) {
        dprintf(client->socket_fd, "[%s] [%s] %d\n", team->user_name[t],
            team->user_uuid[t], get_state_by_uuid(server, team->user_uuid[t]));
    }
}

static void sub_subscribed_team(client_t *client, server_t *server,
    int t, int s)
{
    if (!strcmp(client->uuid, server->teams[t].user_uuid[s])) {
        dprintf(client->socket_fd, "[%s] [%s] [%s]\n", server->teams[t].uuid,
        server->teams[t].name, server->teams[t].description);
    }
}

static void list_subscribed_team(client_t *client, server_t *server)
{
    for (int t = 0; t != MAX_TEAM; t++) {
        for (int s = 0; s != MAX_USERS_TEAM; s++) {
            sub_subscribed_team(client, server, t, s);
        }
    }
}

static int check_error_subscribed(client_t *client, char **args)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (arraylen(args) > 2) {
        return send_message(202, RED, client);
    }
    return SUCCES;
}

int command_subscribed(COMMAND_ARGUMENTS)
{
    int index = 0;
    team_t *team = NULL;

    if (check_error_subscribed(client, args) == ERROR) {
        return ERROR;
    }
    if (arraylen(args) == 2) {
        team = get_team(server, args[1]);
        if (!team) {
            return send_message(207, RED, client);
        }
        send_message(101, GREEN, client);
        list_subscribed_members(server, client, team);
        return send_message(101, GREEN, client);
    }
    send_message(101, GREEN, client);
    list_subscribed_team(client, server);
    send_message(101, GREEN, client);
    return SUCCES;
}
