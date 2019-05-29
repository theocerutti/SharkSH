/*
** EPITECH PROJECT, 2019
** manage_lists2
** File description:
** manage lists chained
*/

#include "exec.h"

void list_insert_between(envlist_t *after, envlist_t *bef, char *k, char *v)
{
    envlist_t *new = malloc(sizeof(*new));

    new->key = NULL;
    new->value = NULL;
    new->key = my_strcpy(k, new->key);
    new->value = my_strcpy(v, new->value);
    bef->next = new;
    new->next = after;
}

void list_supress_elem(fenvlist_t *c, envlist_t *e, envlist_t *b,
envlist_t *a)
{
    if (c == NULL || e == NULL)
        return;
    if (c->first == e) {
        c->first = a;
        free(e);
        return;
    } else if (e->next == NULL) {
        b->next = NULL;
        free(e);
        return;
    }
    b->next = a;
    free(e);
}

void list_affich(fenvlist_t *control, char **env)
{
    envlist_t *ev = control->first;

    if (control == NULL)
        return;
    while (ev != NULL) {
        my_putstr(ev->key);
        if (my_strcmp_cd(ev->key, "OLDPWD") == 1)
            change_old_pwd_value(ev->value, env);
        if (my_strcmp_cd(ev->key, "PWD") == 1)
            change_pwd_value_list(ev->value, env);
        my_putchar('=');
        my_putstr(ev->value);
        my_putchar('\n');
        ev = ev->next;
    }
}