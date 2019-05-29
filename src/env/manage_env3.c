/*
** EPITECH PROJECT, 2019
** manage_env3
** File description:
** manage env
*/

#include "exec.h"

char *my_getenv(char *key, fenvlist_t *env)
{
    envlist_t *actual = NULL;
    int len = strlen(key);

    actual = env->first;
    while (actual != NULL) {
        if (!strncmp(key, actual->key, len))
            return (actual->value);
        if (actual->next == NULL)
            break;
        actual = actual->next;
    }
    return (NULL);
}

void set_values(all_t *all, envlist_t *actual)
{
    if (all->args[2] == NULL) {
        list_insert_last(actual, all->args[1], NULL);
        return;
    } else {
        list_insert_last(actual, all->args[1], all->args[2]);
        return;
    }
}

int setenv2(all_t *all)
{
    if (all->args[1] == NULL) {
        list_affich(all->env, all->ev_exec);
        return (1);
    } else if (all->args[2] != NULL && all->args[3] != NULL) {
        my_puterror("setenv: Too many arguments.\n");
        all->exit_code = 1;
        return (1);
    }
    if ((all->args[1][0] > 90 && all->args[1][0] < 97) \
    || (all->args[1][0] < 65 || all->args[1][0] > 122)) {
        all->exit_code = 1;
        my_puterror("setenv: Variable name must begin with a letter.\n");
        return (1);
    } else if (not_alphanum(all->args[1]) == 1) {
        all->exit_code = 1;
        my_puterror("setenv: Variable name must ");
        my_puterror("contain alphanumeric characters.\n");
        return (1);
    }
    return (0);
}

void my_setenv(all_t *el)
{
    envlist_t *actual = NULL;

    if (setenv2(el) == 1)
        return;
    actual = el->env->first;
    while (actual != NULL) {
        if (my_strcmp_cd(actual->key, el->args[1]) == 1) {
            change_value_env(actual, el->args[2], el, 0);
            return;
        }
        if (actual->next == NULL)
            break;
        actual = actual->next;
    }
    set_values(el, actual);
}