/*
** EPITECH PROJECT, 2024
** client
** File description:
** commands
*/

#ifndef COMMANDS_H_
    #define COMMANDS_H_

    #define COMMAND_INDEX 0
    #define NB_COMMAND 17
    #define UUID_EMPLACEMENT 1
    #define LOGOUT_CODE 42
    #define EXIT_COMMAND_BUILT_IN 1

    #include "client.h"

// !--- FUNCTIONS CLIENT ---! //

int help_command(client_t *client);
int clear(client_t *client);
int login(client_t *client);
int logout(client_t *client);
int users(client_t *client);
int user(client_t *client);
int exit_cli(client_t *client);
int subscribe(client_t *client);
int unsubscribe(client_t *client);
int subscribed(client_t *client);
int create(client_t *client);
int use(client_t *client);
int list(client_t *client);
int info(client_t *client);
int send_command(client_t *client);
int messages(client_t *client);

typedef struct commands_s {
    char *command;
    int (*func)(client_t *);
} commands_t;

static const commands_t cmd[NB_COMMAND] = {

    {"/login", &login},
    {"/logout", &logout},
    {"/help", &help_command},
    {"/users", &users},
    {"/user", &user},
    {"/clear", &clear},
    {"/subscribe", &subscribe},
    {"/unsubscribe", &unsubscribe},
    {"/subscribed", &subscribed},
    {"exit", &exit_cli},
    {"/create", &create},
    {"/use", &use},
    {"/list", &list},
    {"/info", &info},
    {"/send", &send_command},
    {"/messages", &messages},
    {NULL, NULL}

};

#endif /* !COMMANDS_H_ */
