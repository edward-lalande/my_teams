/*
** EPITECH PROJECT, 2024
** server
** File description:
** team
*/

#ifndef TEAM_H_

    #define TEAM_H_

    #include <uuid/uuid.h>
    #include <netinet/in.h>
    #include "channel.h"

    #define TEAM_NAME_EMPLACEMENT 1
    #define MAX_TEAM 16
    #define NAME_LENGTH 32
    #define UUID_LENGTH 37
    #define MAX_USERS_TEAM 16

typedef struct team_s {

    char name[NAME_LENGTH];
    char description[DESCRIPTION_LENGTH];
    uuid_t binuuid;
    char uuid[UUID_LENGTH];

    char user_uuid[MAX_USERS_TEAM][UUID_LENGTH];
    char user_name[MAX_USERS_TEAM][UUID_LENGTH];
    int nb_users;

    channel_t channels[MAX_CHANNEL];

} team_t;


#endif /* !TEAM_H_ */
