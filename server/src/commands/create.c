/*
** EPITECH PROJECT, 2024
** server
** File description:
** create
*/

#include <stdio.h>
#include <string.h>

#include "command.h"
#include "logging_server.h"

int check_not_found(server_t *server, client_t *client, int mode)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = NULL;

    if (mode >= 1 && !team) {
        return send_message(207, RED, client);
    }
    channel = get_channel(team, CHANNEL_CONTEXT);
    if (mode >= 2 && !channel) {
        return send_message(208, RED, client);
    }
    if (mode == 3 && !get_thread(channel, THREAD_CONTEXT)) {
        return send_message(209, RED, client);
    }
    return SUCCES;
}

int check_create_error(client_t *client, char **args, const int size)
{
    if (arraylen(args) < 3) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 3) {
        return send_message(202, RED, client);
    }
    if (strlen(args[1]) > NAME_LENGTH) {
        return send_message(202, RED, client);
    }
    if (strlen(args[2]) > size) {
        return send_message(202, RED, client);
    }
}

static int create_team(COMMAND_ARGUMENTS)
{
    team_t *team = NULL;

    if (check_create_error(client, args, DESCRIPTION_LENGTH) == ERROR) {
        return ERROR;
    }
    for (unsigned int i = 0; i < MAX_TEAM; i++) {
        if (!strcmp(server->teams[i].name, args[1])) {
            return send_message(206, RED, client);
        }
        if (!strcmp(server->teams[i].uuid, "")) {
            team = &server->teams[i];
            sub_create_team(team, args);
            send_message(101, GREEN, client);
            dprintf(client->socket_fd, "Team [%s]\n",
            team->uuid);
            server_event_team_created(team->uuid, team->name, client->uuid);
            return SUCCES;
        }
    }
    return send_message(400, RED, client);
}

static void new_channel(client_t *client, channel_t *channel, char **args)
{
    strcpy(channel->name, args[1]);
    strcpy(channel->description, args[2]);
    uuid_generate(channel->binuuid);
    uuid_unparse(channel->binuuid, channel->uuid);
}

static int create_channel(COMMAND_ARGUMENTS)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = NULL;

    if (check_channel_error(client, server, args) == ERROR) {
        return ERROR;
    }
    for (unsigned int i = 0; i < MAX_CHANNEL; i++) {
        if (!strcmp(team->channels[i].name, args[1]))
            return send_message(206, RED, client);
        if (!strcmp(team->channels[i].uuid, "")) {
            channel = &team->channels[i];
            new_channel(client, channel, args);
            send_message(101, GREEN, client);
            dprintf(client->socket_fd, "Channel [%s]\n", channel->uuid);
            server_event_channel_created(
            team->uuid, channel->uuid, channel->name);
            return SUCCES;
        }
    }
    return send_message(400, RED, client);
}

static void new_thread(client_t *client, thread_t *thread, char **args)
{
    strcpy(thread->name, args[1]);
    uuid_generate(thread->binuuid);
    uuid_unparse(thread->binuuid, thread->uuid);
    strcpy(thread->messages[0].sender, client->uuid);
    strcpy(thread->messages[0].content, args[2]);
    thread->messages[0].timestamp = time(NULL);
}

static int create_thread(COMMAND_ARGUMENTS)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);
    thread_t *thread = NULL;

    if (check_thread_error(client, server, args))
        return ERROR;
    for (unsigned int i = 0; i < MAX_THREAD; i++) {
        if (!strcmp(team->channels[i].name, args[1]))
            return send_message(206, RED, client);
        if (!strcmp(channel->threads[i].uuid, "")) {
            thread = &channel->threads[i];
            send_message(101, GREEN, client);
            new_thread(client, thread, args);
            dprintf(client->socket_fd, "Thread [%s] [%ld]\n", thread->uuid,
            thread->messages[0].timestamp);
            return server_event_thread_created(channel->uuid, thread->uuid,
            client->uuid, args[1], args[2]);
        }
    }
    return send_message(400, RED, client);
}

static int create_reply(COMMAND_ARGUMENTS)
{
    team_t *team = get_team(server, TEAM_CONTEXT);
    channel_t *channel = get_channel(team, CHANNEL_CONTEXT);
    thread_t *thread = get_thread(channel, THREAD_CONTEXT);

    if (check_error_reply(client, server, args) == ERROR)
        return ERROR;
    for (unsigned int i = 0; i < MAX_CHANNEL; i++) {
        if (!strcmp(thread->messages[i].sender, "")) {
            strcpy(thread->messages[i].sender, client->uuid);
            strcpy(thread->messages[i].content, args[1]);
            thread->messages[i].timestamp = time(NULL);
            send_message(101, GREEN, client);
            dprintf(client->socket_fd, "Reply [%s] [%s] [%ld]\n", team->uuid,
            thread->uuid, thread->messages[i].timestamp);
            server_event_reply_created(thread->uuid,
            client->uuid, args[1]);
            return SUCCES;
        }
    }
    return send_message(400, RED, client);
}

static int manage_command_create(COMMAND_ARGUMENTS)
{
    if (client->state != LOGIN) {
        return send_message(204, RED, client);
    }
    if (!strcmp(TEAM_CONTEXT, "")) {
        return create_team(client, server, args);
    }
    if (!strcmp(CHANNEL_CONTEXT, "")) {
        return create_channel(client, server, args);
    }
    if (!strcmp(THREAD_CONTEXT, "")) {
        return create_thread(client, server, args);
    }
    return create_reply(client, server, args);
}

int command_create(COMMAND_ARGUMENTS)
{
    manage_command_create(client, server, args);
    save_server(server);
}
