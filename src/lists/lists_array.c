/*
** EPITECH PROJECT, 2019
** manage_lists
** File description:
** manage chained lists
*/

#include "exec.h"

fenvlist_t *envlist_init(void)
{
    fenvlist_t *control = malloc(sizeof(*control));
    envlist_t *ev = malloc(sizeof(*ev));

    if (control == NULL || ev == NULL)
        exit(84);
    ev->key = NULL;
    ev->value = NULL;
    ev->next = NULL;
    control->first = ev;
    return (control);
}

void list_insert_first(fenvlist_t *control, char *key, char *value)
{
    envlist_t *new = malloc(sizeof(*new));

    if (control == NULL || new == NULL)
        exit(84);
    new->key = NULL;
    new->value = NULL;
    new->key = my_strcpy(key, new->key);
    new->value = my_strcpy(value, new->value);
    new->next = NULL;
    control->first = new;
}

void list_insert_last(envlist_t *before, char *key, char *value)
{
    envlist_t *new = malloc(sizeof(*new));

    new->key = NULL;
    new->value = NULL;
    new->key = my_strcpy(key, new->key);
    new->value = my_strcpy(value, new->value);
    new->next = NULL;
    before->next = new;
}