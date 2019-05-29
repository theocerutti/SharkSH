/*
** EPITECH PROJECT, 2019
** get_arguments2
** File description:
** get arguemnts
*/

#include "exec.h"

char *get_path(char *path, char *str, int idx)
{
    int size = 0;

    for (int i = idx; str[i] != '\0' && str[i] != ':'; i++)
        size++;
    path = malloc(sizeof(char) * (size + 1));
    for (int i = 0; str[idx] != '\0' && str[idx] != ':'; idx++) {
        path[i] = str[idx];
        i++;
    }
    path[size] = '\0';
    return (path);
}

char **path_to_word_array(char **path, char *str)
{
    int idx = 1;
    int size = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ':')
            size++;
    }
    path = malloc(sizeof(char *) * (size + 1));
    path[0] = get_path(path[0], str, 0);
    for (int i = 0; size != 1 && str[i] != '\0'; i++) {
        if (str[i] == ':') {
            path[idx] = get_path(path[idx], str, i + 1);
            idx++;
        }
    }
    path[size] = NULL;
    return (path);
}