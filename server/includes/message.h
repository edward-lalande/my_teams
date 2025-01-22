/*
** EPITECH PROJECT, 2024
** server
** File description:
** messages
*/

#ifndef MESSAGES_H_
    #define MESSAGES_H_

    #define NB_MESSAGES 16
    #define MESSAGE_SIZE 1024

    #include <time.h>

typedef struct server_message_s {

    int code;
    char message[MESSAGE_SIZE];

} server_message_t;

static const server_message_t messages[NB_MESSAGES] = {

    { 100, "Connection succed."},
    { 101, "Request succced."},
    { 200, "Command not found."},
    { 201, "Missing arguments."},
    { 202, "Bad format."},
    { 203, "Already login."},
    { 204, "Not login."},
    { 205, "Not found."},
    { 206, "Already existing."},
    { 207, "Team not found."},
    { 208, "Channel not found."},
    { 209, "Thread not found."},
    { 210, "Too many subscribers in this team."},
    { 211, "Already subscribed"},
    {212, "User is not subscribe to this team"},
    { 400, "Too many creation." }

};

#endif /* !MESSAGES_H_ */
