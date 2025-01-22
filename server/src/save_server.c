/*
** EPITECH PROJECT, 2024
** server
** File description:
** save_server
*/

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "server.h"

static void save_clients(server_t *server)
{
    const int fd = open(SAVE_CLIENTS, O_RDWR | O_TRUNC | O_CREAT, SAVE_RIGHTS);

    if (fd == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (write(fd, server->clients, sizeof(server->clients)) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (close(fd) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
}

static void save_teams(server_t *server)
{
    const int fd = open(SAVE_TEAMS, O_RDWR | O_TRUNC | O_CREAT, SAVE_RIGHTS);

    if (fd == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (write(fd, server->teams, sizeof(server->teams)) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
    if (close(fd) == SYSERR) {
        close_server(server);
        error(ERROR, errno, strerror(errno));
    }
}

void save_server(server_t *server)
{
    save_clients(server);
    save_teams(server);
}
