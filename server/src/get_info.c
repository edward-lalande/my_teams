/*
** EPITECH PROJECT, 2024
** server
** File description:
** get_info
*/

#include <string.h>

#include "server.h"

team_t *get_team(server_t *server, char *uuid)
{
    for (unsigned int i = 0; i < MAX_TEAM; i++) {
        if (!strcmp(server->teams[i].uuid, uuid)) {
            return &server->teams[i];
        }
    }
    return NULL;
}

channel_t *get_channel(team_t *team, char *uuid)
{
    for (unsigned int i = 0; i < MAX_CHANNEL; i++) {
        if (!strcmp(team->channels[i].uuid, uuid)) {
            return &team->channels[i];
        }
    }
    return NULL;
}

thread_t *get_thread(channel_t *channel, char *uuid)
{
    for (unsigned int i = 0; i < MAX_THREAD; i++) {
        if (!strcmp(channel->threads[i].uuid, uuid)) {
            return &channel->threads[i];
        }
    }
    return NULL;
}
