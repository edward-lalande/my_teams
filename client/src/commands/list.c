/*
** EPITECH PROJECT, 2024
** client
** File description:
** list
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "logging_client.h"

static bool is_code_line(char *line)
{
    for (int i = 0; line[i]; i++) {
        if (line[i] == ']') {
            return false;
        }
    }
    return true;
}

static void list_team(void)
{
    char *name = strtok(NULL, " []");
    char *description = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");

    client_print_teams(uuid, name, description);
}

static void list_channel(void)
{
    char *name = strtok(NULL, " []");
    char *description = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");

    client_team_print_channels(uuid, name, description);
}

static void list_thread(void)
{
    char *name = strtok(NULL, " []");
    char *sender = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");
    char *time = strtok(NULL, " []");
    char *body = strtok(NULL, "\n");

    client_channel_print_threads(uuid, sender, (time_t)atoi(time), name, body);
}

static void list_reply(void)
{
    char *sender = strtok(NULL, " []");
    char *thread_uuid = strtok(NULL, " []");
    char *time = strtok(NULL, " []");
    char *content = strtok(NULL, "\n");

    client_thread_print_replies(thread_uuid, sender,
    (time_t)atoi(time), content);
}

static int manage_list(client_t *client)
{
    char *type = NULL;
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, client->server);
    while (!is_code_line(line)) {
        dprintf(1, line);
        type = strtok(line, " ");
        if (!strcmp(type, "Team"))
            list_team();
        if (!strcmp(type, "Channel"))
            list_channel();
        if (!strcmp(type, "Thread"))
            list_thread();
        if (!strcmp(type, "Reply"))
            list_reply();
        getline(&line, &len, client->server);
    }
    dprintf(1, line);
    return EXIT_WITH_SUCCESS;
}

static int check_error_list(client_t *client, char *line)
{
    if (!client->is_connected) {
        client_error_unauthorized();
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) == 207) {
        client_error_unknown_team(client->team_context);
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) == 208) {
        client_error_unknown_channel(client->channel_context);
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) == 209) {
        client_error_unknown_thread(client->thread_context);
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    return EXIT_WITH_SUCCESS;
}

int list(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, client->line);
    getline(&line, &len, client->server);
    dprintf(1, line);
    if (check_error_list(client, line) == EXIT_WITH_ERROR) {
        return EXIT_WITH_ERROR;
    }
    if (get_code(line) >= 200) {
        return EXIT_WITH_ERROR;
    }
    return manage_list(client);
}
