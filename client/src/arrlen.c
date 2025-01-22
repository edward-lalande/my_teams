/*
** EPITECH PROJECT, 2024
** client
** File description:
** arrlen
*/

#include <stddef.h>

int arrlen(char **arr)
{
    int i = 0;

    while (arr[i] != NULL) {
        ++i;
    }
    return i;
}
