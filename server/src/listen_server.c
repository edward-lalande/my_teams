/*
** EPITECH PROJECT, 2024
** server
** File description:
** listen_server
*/

#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#include "command.h"
#include "server.h"

bool is_running(int mode, bool state)
{
    static bool is_running = true;

    if (mode == SET) {
        is_running = state;
        return is_running;
    }
    return (is_running == state);
}

void catch_sigint(__attribute__((unused)) int signal)
{
    is_running(SET, false);
}

static void logout_all_client(server_t *server)
{
    char *args[] = { "/logout", NULL};

    for (size_t i = 0; i < SOMAXCONN; ++i) {
        if (server->clients[i].state == LOGIN
            && server->clients[i].socket_fd != 0) {
                command_logout(&server->clients[i], server, args);
        }
    }
}

void listen_server(server_t *server)
{
    if (listen(server->socket_fd, SOMAXCONN) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    is_running(SET, true);
    signal(SIGINT, &catch_sigint);
    while (is_running(GET, true)) {
        set_clients(server);
        check_connection(server);
        check_command(server);
    }
    logout_all_client(server);
    check_command(server);
}
