/*
** EPITECH PROJECT, 2024
** server
** File description:
** private_discussion
*/

#ifndef PRIVATE_DISCUSSION_H_
    #define PRIVATE_DISCUSSION_H_

    #define BODY_LENGTH 512
    #define UUID_LENGTH 37
    #define MAX_MESSAGE 64

    #include <time.h>

typedef struct message_s {

    char sender[UUID_LENGTH];
    char content[BODY_LENGTH];

    time_t timestamp;

} message_t;

typedef struct discussion_s {

    char user[UUID_LENGTH];

    message_t messages[MAX_MESSAGE];

} discussion_t;

#endif /* !PRIVATE_DISCUSSION_H_ */
