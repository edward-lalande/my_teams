/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-paul.bardeur
** File description:
** thread
*/

#ifndef THREAD_H_
    #define THREAD_H_

    #include <uuid/uuid.h>
    #include "discussion.h"

    #define MAX_THREAD 16
    #define NAME_LENGTH 32
    #define UUID_LENGTH 37
    #define DESCRIPTION_LENGTH 255

typedef struct thread_s {

    char name[NAME_LENGTH];

    uuid_t binuuid;
    char uuid[UUID_LENGTH];

    message_t messages[MAX_MESSAGE];

} thread_t;


#endif /* !THREAD_H_ */
