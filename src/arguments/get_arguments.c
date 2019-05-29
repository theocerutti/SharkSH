/*
** EPITECH PROJECT, 2019
** get_arguments
** File description:
** get_arguments
*/

#include "exec.h"

char *values(char *value, char **key, char *str)
{
    int idx = 0;
    int size = 0;
    int i = 0;

    for (; str[size] != '='; size++);
    idx = size + 1;
    key[0] = malloc(sizeof(char) * (size + 1));
    key[0][size] = '\0';
    for (size = 0; str[idx] != '\0'; idx++, size++);
    value = malloc(sizeof(char) * (size + 1));
    value[size] = '\0';
    for (idx = 0; str[idx] != '='; idx++) {
        key[0][i] = str[idx];
        i++;
    }
    for (i = 0, idx = idx + 1; str[idx] != '\0'; idx++) {
        value[i] = str[idx];
        i++;
    }
    return (value);
}

fenvlist_t *get_env(all_t *all, char **str)
{
    fenvlist_t *list = envlist_init();
    envlist_t *actual = NULL;
    char *key = NULL;
    char *value = NULL;

    all = all;
    value = values(value, &key, str[0]);
    list_insert_first(list, key, value);
    free(key);
    free(value);
    actual = list->first;
    for (int i = 1; str[i] != NULL; i++) {
        value = values(value, &key, str[i]);
        list_insert_last(actual, key, value);
        free(key);
        free(value);
        actual = actual->next;
    }
    return (list);
}

char *pwd_go_back(all_t *all)
{
    char *new = NULL;
    char *ret = NULL;
    int idx = 0;
    int size = 0;

    new = inspect_namedir(all->current, NULL);
    for (int i = 0; new[i] != '\0'; i++) {
        if (new[i] == '/')
            idx = i;
    }
    for (int i = idx; new[i] != '\0'; i++)
        size++;
    ret = malloc(sizeof(char) * (my_strlen(new) - size + 1));
    for (int i = 0; i < idx; i++)
        ret[i] = new[i];
    ret[idx] = '\0';
    return (ret);
}

void go_back_dir(all_t *all)
{
    char *new = NULL;
    int idx = 0;
    int size = 0;

    new = my_strcpy(all->current, new);
    free(all->current);
    for (int i = 0; new[i] != '\0'; i++) {
        if (new[i] == '/')
            idx = i;
    }
    for (int i = idx; new[i] != '\0'; i++)
        size++;
    all->current = malloc(sizeof(char) * (my_strlen(new) - size + 1));
    for (int i = 0; i < idx; i++)
        all->current[i] = new[i];
    all->current[idx] = '\0';
    free(new);
}