/*
** EPITECH PROJECT, 2024
** server
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <uuid/uuid.h>
    #include <netinet/in.h>

    #include "discussion.h"

    #define NAME_LENGTH 32
    #define DESCRIPTION_LENGTH 255
    #define UUID_LENGTH 37
    #define MAX_DISCUSSION 32

    #define ERROR 84
    #define SUCCES 0

    #define GREEN 32
    #define RED 31

typedef enum client_state_e {

    DEFAULT,
    LOGOUT,
    LOGIN

} client_state_t;

typedef struct client_s {

    int socket_fd;
    char name[NAME_LENGTH];

    uuid_t binuuid;
    char uuid[UUID_LENGTH];

    char team_context[UUID_LENGTH];
    char channel_context[UUID_LENGTH];
    char thread_context[UUID_LENGTH];

    client_state_t state;

    discussion_t discussions[MAX_DISCUSSION];

} client_t;

int send_message(const int code, const int color, const client_t *client);

#endif /* !CLIENT_H_ */
