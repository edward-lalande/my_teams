/*
** EPITECH PROJECT, 2024
** client
** File description:
** catch_sigint
*/

#include <stdio.h>

void catch_sigint(int val)
{
    (void)val;
    dprintf(1, "\n$> ");
}
