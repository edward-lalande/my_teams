/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/select.h>
    #include <netinet/in.h>
    #include <stdbool.h>

    #include "client.h"
    #include "team.h"

    #define ERROR 84
    #define SUCCES 0

    #define SET 0
    #define GET 1

    #define SYSERR -1

    #define SAVE_CLIENTS "DATABASE_CLIENTS.pet"
    #define SAVE_TEAMS "DATABASE_TEAMS.pet"
    #define SAVE_RIGHTS 0644

    #define WHITE 37
    #define GREEN 32
    #define RED 31

    #define MAX_SIZE 1024

    #define NB_ARGS_REQUIRED 2

typedef struct server_s {

    int max_sd;
    int port;
    int socket_fd;
    fd_set readfs;
    client_t clients[SOMAXCONN];
    struct timeval time;
    struct sockaddr_in address;

    team_t teams[MAX_TEAM];

} server_t;

int usage(void);
int server(const int port);

server_t *get_server(const int port);

void listen_server(server_t *server);
void set_clients(server_t *server);
void check_connection(server_t *server);
int check_command(server_t *server);

void save_server(server_t *server);

int close_server(server_t *server);

void display_message(const char *message, const int color);

#endif /* !SERVER_H_ */
