/*
** EPITECH PROJECT, 2024
** server
** File description:
** display_message
*/

#include <stdio.h>

#include "server.h"

void display_message(const char *message, const int color)
{
    dprintf(1, "\033[0;%dm%s\n", color, message);
    dprintf(1, "\033[0m");
}
