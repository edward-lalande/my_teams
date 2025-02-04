/*
** EPITECH PROJECT, 2022
** my
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>

void free_array(char **array)
{
    for (int i = 0; array && array[i]; i++) {
        free(array[i]);
    }
    if (array) {
        free(array);
    }
}

int is_alpha_num(char c)
{
    if ((c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9')
        || c == '-' || c == '.'
        || c == '~' || c == '/'
        || c == '>' || c == '\"'
        || c == '&' || c == ';'
        || c == '<' || c == '|'
        || c == '$') {
            return 1;
        }
    return 0;
}

int count_delim(char *str, char delim)
{
    int nb_space = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == delim || str[i] == '\t')
            nb_space++;
    return nb_space + 1;
}

char *put_in_arr(int i, int j, char *str)
{
    char *new_str = malloc(sizeof(char) * ((i - j) + 2));
    int n = 0;

    while (j < i) {
        if (str[j] == ' ' && !(is_alpha_num(str[j + 1]))) {
            j++;
            continue;
        }
        new_str[n] = str[j];
        j++;
        n++;
    }
    new_str[n] = '\0';
    return new_str;
}

char **my_str_to_word_array(char *str, char delim)
{
    int nb_delim = count_delim(str, delim);
    int nb_arr = 0;
    int i = 0;
    int j = 0;
    char **arr = malloc(sizeof(char *) * (nb_delim + 2));

    while (nb_arr != nb_delim) {
        if (str[i] == delim || str[i] == '\0') {
            arr[nb_arr] = put_in_arr(i, j, str);
            i++;
            j = i;
            nb_arr++;
        }
        i++;
    }
    arr[nb_arr] = NULL;
    return arr;
}
