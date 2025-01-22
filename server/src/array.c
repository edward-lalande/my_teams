/*
** EPITECH PROJECT, 2024
** server
** File description:
** array
*/

int arraylen(char **array)
{
    int len = 0;

    while (array && array[len]) {
        len += 1;
    }
    return len;
}
