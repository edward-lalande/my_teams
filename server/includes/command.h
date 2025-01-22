/*
** EPITECH PROJECT, 2024
** server
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "server.h"

    #define NB_COMMANDS 14

    #define COMMAND_ARGUMENTS client_t *client, server_t *server, char **args

    #define TEAM_CONTEXT client->team_context
    #define CHANNEL_CONTEXT client->channel_context
    #define THREAD_CONTEXT client->thread_context

typedef struct command_s {

    char *command;
    int (*function)(COMMAND_ARGUMENTS);

} command_t;

team_t *get_team(server_t *server, char *uuid);
channel_t *get_channel(team_t *team, char *uuid);
thread_t *get_thread(channel_t *channel, char *uuid);

int check_not_found(server_t *server, client_t *client, int mode);

int check_create_error(client_t *client, char **args, const int size);
void sub_create_team(team_t *team, char **args);
int check_channel_error(COMMAND_ARGUMENTS);
int check_thread_error(COMMAND_ARGUMENTS);
int check_error_reply(COMMAND_ARGUMENTS);


int arraylen(char **array);

int command_help(COMMAND_ARGUMENTS);
int command_login(COMMAND_ARGUMENTS);
int command_logout(COMMAND_ARGUMENTS);
int command_users(COMMAND_ARGUMENTS);
int command_user(COMMAND_ARGUMENTS);
int command_send(COMMAND_ARGUMENTS);
int command_messages(COMMAND_ARGUMENTS);
int command_use(COMMAND_ARGUMENTS);
int command_create(COMMAND_ARGUMENTS);
int command_list(COMMAND_ARGUMENTS);
int command_unsubscribe(COMMAND_ARGUMENTS);
int command_subscribe(COMMAND_ARGUMENTS);
int command_subscribed(COMMAND_ARGUMENTS);
int command_info(COMMAND_ARGUMENTS);

static const command_t commands[NB_COMMANDS] = {

    {"/help", command_help},
    {"/login", command_login},
    {"/logout", command_logout},
    {"/users", command_users},
    {"/user", command_user},
    {"/send", command_send},
    {"/messages", command_messages},
    {"/use", command_use},
    {"/create", command_create},
    {"/list", command_list},
    {"/subscribe", command_subscribe},
    {"/subscribed", command_subscribed},
    {"/unsubscribe", command_unsubscribe},
    {"/info", command_info}

};

#endif /* !COMMAND_H_ */
