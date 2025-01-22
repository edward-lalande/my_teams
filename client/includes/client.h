/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include <stdio.h>

    #define EXIT_WITH_ERROR 84
    #define EXIT_WITH_SUCCESS 0

    #define LOGOUT_CODE 42

    #define BEGIN_OF_ERROR_CODE 200

    #define ERROR -1

    #define CRLF '\r\n'

    #define IP 1
    #define PORT 2

    #define NB_ARGS_REQUIRED 3

    #define UUID_LENGTH 37
    #define MAX_NAME_LENGTH 32

typedef struct client_s {

    struct sockaddr_in serv_addr;
    int sock_fd;
    char **command;
    char *line;
    struct sockaddr client;
    bool is_connected;

    FILE *server;

    fd_set readfds;
    fd_set writefds;
    fd_set fd;

    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH];

    char team_context[UUID_LENGTH];
    char channel_context[UUID_LENGTH];
    char thread_context[UUID_LENGTH];

} client_t;

// !--- LIB ---! //

char **my_str_to_word_array(char *str, char delim);
int arrlen(char **arr);
void free_array(char **array);

// !--- CORE TEAMS CLIENT ---! //

int teams_client(char *ip, char *port);
void display_prompt(void);
int get_code(char *line);

// !--- COMMUNICATION ---! //

void send_and_print_server_response(client_t *client, char *buffer);

// !--- INIT TEAMS CLIENT ---! //

client_t *init_teams_client(char *port);

// !--- SEARCH COMMANDS ---! //

int search_command(client_t *client);

// !--- CATCH SIGNALS ---! //

void catch_sigint(int val);
void catch_sigpipe(int val);
void catch_sigsev(int val);

// !--- HELP ---! //

void print_usage(void);

#endif /* !CLIENT_H_ */
