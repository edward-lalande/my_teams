/*
** EPITECH PROJECT, 2024
** list command
** File description:
** myTEams proj
*/

#include <stdio.h>
#include <string.h>

#include "command.h"

#include "logging_server.h"

static char *get_name_by_uuid(server_t *server, char *uuid)
{
    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        if (!strcmp(server->clients[i].uuid, uuid)) {
            return server->clients[i].name;
        }
    }
    return "";
}

static int list_team(server_t *server, client_t *client)
{
    send_message(101, GREEN, client);
    for (unsigned int t = 0; t < MAX_TEAM; t++) {
        if (!strcmp(server->teams[t].uuid, "")) {
            continue;
        }
        dprintf(client->socket_fd, "Team %s", server->teams[t].name);
        dprintf(client->socket_fd, " [%s] [%s]\n",
        server->teams[t].description, server->teams[t].uuid);
    }
    send_message(101, GREEN, client);
    return SUCCES;
}

static int list_channel(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);

    if (!team) {
        return send_message(207, RED, client);
    }
    send_message(101, GREEN, client);
    for (unsigned int t = 0; t < MAX_CHANNEL; t++) {
        if (!strcmp(team->channels[t].uuid, "")) {
            continue;
        }
        dprintf(client->socket_fd, "Channel %s", team->channels[t].name);
        dprintf(client->socket_fd, " [%s] [%s]\n",
        team->channels[t].description, team->channels[t].uuid);
    }
    send_message(101, GREEN, client);
    return SUCCES;
}

static int list_thread(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);

    if (check_not_found(server, client, 2) == ERROR) {
        return ERROR;
    }
    send_message(101, GREEN, client);
    for (unsigned int t = 0; t < MAX_CHANNEL; t++) {
        if (!strcmp(channel->threads[t].uuid, "")) {
            continue;
        }
        dprintf(client->socket_fd, "Thread [%s]", channel->threads[t].name);
        dprintf(client->socket_fd, " [%s] [%s] [%ld]",
            channel->threads[t].messages[0].sender, channel->threads[t].uuid,
            channel->threads[t].messages[0].timestamp);
        dprintf(client->socket_fd, "%s\n",
            channel->threads[t].messages[0].content);
    }
    send_message(101, GREEN, client);
    return SUCCES;
}

static int list_replies(server_t *server, client_t *client)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);
    thread_t *thread = get_thread(channel, THREAD_CONTEXT);
    char *name = NULL;

    if (check_not_found(server, client, 3) == ERROR)
        return ERROR;
    send_message(101, GREEN, client);
    for (unsigned int t = 0; t < MAX_CHANNEL; t++) {
        if (!strcmp(thread->messages[t].sender, ""))
            continue;
        name = get_name_by_uuid(server, thread->messages[t].sender);
        dprintf(client->socket_fd, "Reply [%s] [%s] [%ld]", name, thread->uuid,
        thread->messages[t].timestamp);
        dprintf(client->socket_fd, "%s\n", thread->messages[t].content);
    }
    send_message(101, GREEN, client);
    return SUCCES;
}

int command_list(COMMAND_ARGUMENTS)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (arraylen(args) > 1) {
        return send_message(202, RED, client);
    }
    if (!strcmp(client->team_context, "")) {
        return list_team(server, client);
    }
    if (!strcmp(client->channel_context, "")) {
        return list_channel(server, client);
    }
    if (!strcmp(client->thread_context, "")) {
        return list_thread(server, client);
    }
    return list_replies(server, client);
}
