/*
** EPITECH PROJECT, 2024
** info cmd
** File description:
** teams proj
*/

#include <stdio.h>
#include <string.h>

#include "command.h"

static int nocontext_info(server_t *server, client_t *client)
{
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "User [%s]", client->name);
    dprintf(client->socket_fd, " [%s] [%d]\n",
        client->uuid, client->state - 1);
    return SUCCES;
}

static int info_teams(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);

    if (!team) {
        return send_message(207, RED, client);
    }
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "Team [%s]", team->name);
    dprintf(client->socket_fd, " [%s] [%s]\n", team->uuid, team->description);
    return SUCCES;
}

static int info_channels(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);

    if (check_not_found(server, client, 2) == ERROR) {
        return ERROR;
    }
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "Channel [%s]", channel->name);
    dprintf(client->socket_fd, " [%s] [%s]\n", channel->uuid,
        channel->description);
    return SUCCES;
}

static int info_threads(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);
    thread_t *thread = get_thread(channel, THREAD_CONTEXT);

    if (check_not_found(server, client, 3) == ERROR) {
        return ERROR;
    }
    send_message(101, GREEN, client);
    dprintf(client->socket_fd, "Thread [%s]", thread->name);
    dprintf(client->socket_fd, " [%s] [%s] [%ld]", thread->uuid,
        thread->messages[0].sender, thread->messages[0].timestamp);
    dprintf(client->socket_fd, "%s\n", thread->messages[0].content);
    return SUCCES;
}

int command_info(COMMAND_ARGUMENTS)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (arraylen(args) > 1) {
        return send_message(202, RED, client);
    }
    if (!strcmp(client->team_context, "")) {
        return nocontext_info(server, client);
    }
    if (!strcmp(client->channel_context, "")) {
        return info_teams(server, client);
    }
    if (!strcmp(client->thread_context, "")) {
        return info_channels(server, client);
    }
    return info_threads(server, client);
}
