/*
** EPITECH PROJECT, 2024
** client
** File description:
** help
*/

#include <stdio.h>
#include "commands.h"
#include "client.h"

static void help_command_suite(client_t *client)
{
    (void)client;
    dprintf(1, "/subscribed ?[“team_uuid”] -> list all subscribed ");
    dprintf(1, "teams or list all users subscribed to a team\n");
    dprintf(1, "/unsubscribe [“team_uuid”] -> unsubscribe from a team");
    dprintf(1, "/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"]");
    dprintf(1, " -> Sets the command context to a team/channel/thread\n");
    dprintf(1, "/create -> based on the context, create the sub resource\n");
    dprintf(1, "/list -> based on the context, list all the sub resources\n");
    dprintf(1, "/info -> based on the context, display details of ");
    dprintf(1, "the current resource\n");
}

int help_command(client_t *client)
{
    dprintf(1, "/help -> help message\n");
    dprintf(1, "/login [“user_name”] -> login to the server\n");
    dprintf(1, "/logout -> disconnect you from the server\n");
    dprintf(1, "/users -> list all the users on the dommain\n");
    dprintf(1, "/user -> get details about the requested user\n");
    dprintf(1, "/send [“user_uuid”] [“message_body”] ->");
    dprintf(1, " send a message to specific user\n");
    dprintf(1, "/messages [“user_uuid”] ->");
    dprintf(1, "list allmessages exchanged with the specified user\n");
    dprintf(1, "/messages [“user_uuid”] ->");
    dprintf(1, "list all messages exchanged with the specified user\n");
    dprintf(1, "/subscribe [“team_uuid”] -> subscribe to the events of");
    dprintf(1, "a team and its sub directories");
    dprintf(1, "(enable reception of all events from a team)\n");
    help_command_suite(client);
    return EXIT_COMMAND_BUILT_IN;
}
