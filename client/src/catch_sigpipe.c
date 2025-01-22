/*
** EPITECH PROJECT, 2024
** client
** File description:
** catch_sigpipe
*/

#include <stdio.h>

void catch_sigpipe(int val)
{
    (void)val;
    dprintf(1, "\033[0;31m300: Unable to join serveur.\033[0m\n");
}
