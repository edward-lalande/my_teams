/*
** EPITECH PROJECT, 2024
** info cmd
** File description:
** myTeams Proj
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "commands.h"
#include "logging_client.h"
#include "client.h"
#include <time.h>

static void info_user(void)
{
    char *name = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");
    char *state = strtok(NULL, " []");

    client_print_user(uuid, name, atoi(state));
}

static void info_team(void)
{
    char *name = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");
    char *description = strtok(NULL, " []");

    client_print_team(uuid, name, description);
}

static void info_channel(void)
{
    char *name = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");
    char *description = strtok(NULL, " []");

    client_print_channel(uuid, name, description);
}

static void info_thread(void)
{
    char *name = strtok(NULL, " []");
    char *uuid = strtok(NULL, " []");
    char *sender = strtok(NULL, " []");
    char *time = strtok(NULL, " []");
    char *body = strtok(NULL, "\n");

    client_print_thread(uuid, sender, (time_t)atoi(time), name, body);
}

static int management_info(client_t *client)
{
    char *type = NULL;
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, client->server);
    dprintf(1, line);
    type = strtok(line, " ");
    if (!strcmp(type, "User"))
        info_user();
    if (!strcmp(type, "Team"))
        info_team();
    if (!strcmp(type, "Channel"))
        info_channel();
    if (!strcmp(type, "Thread"))
        info_thread();
    return EXIT_WITH_SUCCESS;
}

static int check_error_info(client_t *client, char *line)
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

int info(client_t *client)
{
    char *line = NULL;
    size_t len = 0;

    dprintf(client->sock_fd, client->line);
    getline(&line, &len, client->server);
    dprintf(1, line);
    if (check_error_info(client, line) == EXIT_WITH_ERROR) {
        return EXIT_WITH_ERROR;
    }
    return management_info(client);
}
