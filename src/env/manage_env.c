/*
** EPITECH PROJECT, 2019
** manage_env
** File description:
** manage_env
*/

#include "exec.h"

int not_alphanum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!ALPHANUMERIC(str[i]))
            return (1);
    }
    return (0);
}

void remove_value(envlist_t *ev, int size)
{
    (void)size;
    ev->value = malloc(sizeof(char) * 1);
    ev->value[0] = '\0';
}

void env_parsing(char *name, all_t *all)
{
    envlist_t *actual = NULL;
    envlist_t *tmp = NULL;

    actual = all->env->first;
    while (actual->next != NULL) {
        tmp = actual;
        actual = actual->next;
        if (my_strcmp(actual->key, name) == 0) {
            list_supress_elem(all->env, actual, tmp, actual->next);
            return;
        }
    }
    return;
}

void my_unsetenv(all_t *all)
{
    if (all->args[1] == NULL) {
        my_puterror("unsetenv: Too few arguments.\n");
        all->exit_code = 1;
        return;
    }
    for (int i = 1; all->args[i] != NULL; i++) {
        env_parsing(all->args[i], all);
    }
    return;
}

void my_env(all_t *all)
{
    list_affich(all->env, all->ev_exec);
    return;
}