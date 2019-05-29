/*
** EPITECH PROJECT, 2019
** change_old_pwd
** File description:
** changes old pwd value
*/

#include "exec.h"

char *value_pwd(char *str, char *dest)
{
    int idx = 0;
    int i = 0;

    for (; str[idx] != '='; idx++);
    idx++;
    dest = malloc(sizeof(char) * (my_strlen(str) - idx + 1));
    for (; str[idx] != '\0'; idx++) {
        dest[i] = str[idx];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *get_old_pwd(all_t *all)
{
    envlist_t *actual = NULL;
    char *old = NULL;

    actual = all->env->first;
    while (actual != NULL) {
        if (my_strcmp(actual->key, "OLDPWD") == 0) {
            old = my_strcpy(actual->value, old);
            return (old);
        }
        if (actual->next == NULL)
            break;
        actual = actual->next;
    }
    return (NULL);
}

int change_old_pwd(all_t *all, char *aff)
{
    envlist_t *actual = NULL;

    actual = all->env->first;
    while (actual != NULL) {
        if (my_strcmp(actual->key, "OLDPWD") == 0) {
            free(actual->value);
            actual->value = my_strcpy(aff, actual->value);
            return (0);
        }
        if (actual->next == NULL)
            break;
        actual = actual->next;
    }
    return (-1);
}