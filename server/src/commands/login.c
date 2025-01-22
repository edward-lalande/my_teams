/*
** EPITECH PROJECT, 2024
** server
** File description:
** login
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"
#include "logging_server.h"

static int check_login_errors(COMMAND_ARGUMENTS)
{
    if (arraylen(args) < 2) {
        return send_message(201, RED, client);
    }
    if (arraylen(args) > 2) {
        return send_message(202, RED, client);
    }
    if (client->state == LOGIN) {
        return send_message(203, RED, client);
    }
    if (strlen(args[1]) > NAME_LENGTH) {
        return send_message(202, RED, client);
    }
    return SUCCES;
}

static int check_user_exist(COMMAND_ARGUMENTS)
{
    bool same_name = false;
    bool already_login = false;

    for (unsigned int i = 0; i < SOMAXCONN; i++) {
        same_name = !strcmp(server->clients[i].name, args[1]);
        already_login = server->clients[i].state == LOGIN;
        if (same_name && already_login) {
            return send_message(203, RED, client);
        }
        if (same_name) {
            server->clients[i].socket_fd = client->socket_fd;
            server->clients[i].state = LOGIN;
            send_message(101, GREEN, &server->clients[i]);
            dprintf(client->socket_fd, "Uuid: %s\n", server->clients[i].uuid);
            server_event_user_logged_in(server->clients[i].uuid);
            memset(client, 0, sizeof(client));
            return ERROR;
        }
    }
    return SUCCES;
}

int command_login(COMMAND_ARGUMENTS)
{
    if (check_login_errors(client, server, args) == ERROR) {
        return ERROR;
    }
    if (check_user_exist(client, server, args) == ERROR) {
        return ERROR;
    }
    strcpy(client->name, args[1]);
    client->state = LOGIN;
    uuid_generate(client->binuuid);
    send_message(101, GREEN, client);
    uuid_unparse(client->binuuid, client->uuid);
    dprintf(client->socket_fd, "Uuid: %s\n", client->uuid);
    save_server(server);
    server_event_user_created(client->uuid, client->name);
    return SUCCES;
};
