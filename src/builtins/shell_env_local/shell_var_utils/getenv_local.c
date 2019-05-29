/*
** EPITECH PROJECT, 2019
** getenv_local
** File description:
** getenv_local
*/

#include "exec.h"

const char *my_getenv_local(list_t *var_local, char *key)
{
    node_t *tmp = *var_local;

    while (tmp != NULL) {
        if (!strncmp(tmp->var.key, key, strlen(tmp->var.key)))
            return (tmp->var.value);
        tmp = tmp->next;
    }
    return (NULL);
}