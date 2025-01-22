/*
** EPITECH PROJECT, 2024
** list
** File description:
** client inmyteamsproj
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "logging_client.h"
#include "client.h"
#include <time.h>

static int check_channel_thread(client_t *client, char *type, char *uuid)
{
    char *time = NULL;

    if (!strcmp(type, "Channel")) {
        client_print_channel_created(uuid, client->command[1],
        client->command[2]);
        client_event_channel_created(uuid, client->command[1],
        client->command[2]);
        return EXIT_WITH_SUCCESS;
    }
    if (!strcmp(type, "Thread")) {
        time = strtok(NULL, " []");
        client_print_thread_created(uuid, client->uuid, (time_t)atoi(time),
        client->command[1], client->command[2]);
        client_event_thread_created(uuid, client->uuid, (time_t)atoi(time),
        client->command[1], client->command[2]);
        return EXIT_WITH_SUCCESS;
    }
    return ERROR;
}

static int check_type(client_t *client, char *type, char *uuid)
{
    if (!strcmp(type, "Team")) {
        client_print_team_created(uuid, client->command[1],
        client->command[2]);
        client_event_team_created(uuid, client->command[1],
        client->command[2]);
        return EXIT_WITH_SUCCESS;
    }
    return check_channel_thread(client, type, uuid);
}

static int management_create(client_t *client, char *line, size_t len)
{
    char *type = NULL;
    char *uuid = NULL;
    char *uuid_thread = NULL;
    char *time_stamp = NULL;

    getline(&line, &len, client->server);
    dprintf(1, line);
    type = strtok(line, " ");
    uuid = strtok(NULL, " []");
    time_stamp = strtok(NULL, " []");
    if (check_type(client, type, uuid) == EXIT_WITH_SUCCESS) {
        return EXIT_WITH_SUCCESS;
    }
    uuid_thread = strtok(NULL, " []");
    client_event_thread_reply_received(uuid, uuid_thread,
    client->uuid, client->command[1]);
    client_print_reply_created(uuid_thread, client->uuid,
    (time_t)atoi(time_stamp), client->command[1]);
    return EXIT_WITH_SUCCESS;
}

static int check_create_errors(client_t *client, char *line)
{
    if (get_code(line) == 206) {
        client_error_already_exist();
        return ERROR;
    }
    if (get_code(line) == 207) {
        client_error_unknown_team(client->command[1]);
        return ERROR;
    }
    if (get_code(line) == 208) {
        client_error_unknown_channel(client->command[1]);
        return ERROR;
    }
    if (get_code(line) == 209) {
        client_error_unknown_thread(client->command[1]);
        return ERROR;
    }
    if (get_code(line) >= 200) {
        return ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

int create(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, client->line);
    getline(&line, &len, client->server);
    dprintf(1, line);
    if (!client->is_connected) {
        client_error_unauthorized();
        return EXIT_WITH_ERROR;
    }
    if (check_create_errors(client, line) == ERROR) {
        return EXIT_WITH_ERROR;
    }
    return management_create(client, line, len);
}
