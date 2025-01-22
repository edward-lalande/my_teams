/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** channel
*/

#ifndef CHANNEL_H_
    #define CHANNEL_H_

    #include <uuid/uuid.h>
    #include "thread.h"
    #include "discussion.h"

    #define MAX_CHANNEL 16
    #define TEAM_NAME_EMPLACEMENT 1
    #define NAME_LENGTH 32
    #define UUID_LENGTH 37
    #define DESCRIPTION_LENGTH 255

typedef struct channel_s {

    char name[NAME_LENGTH];
    char description[DESCRIPTION_LENGTH];

    uuid_t binuuid;
    char uuid[UUID_LENGTH];

    thread_t threads[MAX_THREAD];

} channel_t;


#endif /* !CHANNEL_H_ */
