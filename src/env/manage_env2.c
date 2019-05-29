/*
** EPITECH PROJECT, 2019
** manage_env2
** File description:
** manage env
*/

#include "exec.h"

char **get_array_env(char **env)
{
    int size = 0;
    char **ev = NULL;
    int id = 0;

    for (; env[size] != NULL; size++);
    ev = malloc(sizeof(char *) * (size + 1));
    ev[size] = NULL;
    size = 0;
    for (int i = 0; env[i] != NULL; i++) {
        for (int j = 0; env[i][j] != '\0'; j++)
            size++;
        ev[i] = malloc(sizeof(char) * (size + 1));
        size = 0;
        for (id = 0; env[i][id] != '\0'; id++)
            ev[i][id] = env[i][id];
        ev[i][id] = '\0';
    }
    return (ev);
}

void change_value_env(envlist_t *ev, char *str, all_t *all, int det)
{
    int size = 0;

    if (all->args[1] != NULL && all->args[2] == NULL && det == 0) {
        remove_value(ev, size);
        return;
    }
    free(ev->value);
    ev->value = my_strcpy(str, ev->value);
}

char *get_new_env(char *str, char *add, int idx)
{
    char *new = NULL;

    if (add == NULL)
        new = malloc(sizeof(char) * (my_strlen(str) + 2));
    else
        new = malloc(sizeof(char) * (my_strlen(str) + my_strlen(add) + 2));
    for (int i = 0; str[i] != '\0'; i++) {
        new[idx] = str[i];
        idx++;
    }
    new[idx] = '=';
    idx++;
    for (int i = 0; add != NULL && add[i] != '\0'; i++) {
        new[idx] = add[i];
        idx++;
    }
    new[idx] = '\0';
    return (new);
}