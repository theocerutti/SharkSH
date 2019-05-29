/*
** EPITECH PROJECT, 2019
** get_names
** File description:
** get_names file or dir
*/

#include "exec.h"

char *get_new(char *home, char *new, char *path, char *dir)
{
    int idx = 0;

    for (; home[idx] != '\0'; idx++)
        new[idx] = home[idx];
    for (int i = 1; path != NULL && path[i] != '\0'; i++) {
        new[idx] = path[i];
        idx++;
    }
    if (dir != NULL) {
        new[idx] = '/';
        idx++;
    }
    for (int i = 0; dir != NULL && dir[i] != '\n' && dir[i] != '\0'; i++) {
        new[idx] = dir[i];
        idx++;
    }
    new[idx] = '\0';
    return (new);
}

char *inspect_namedir(char *path, char *dir)
{
    char *new = NULL;
    int size = 0;

    if (path != NULL)
        size = my_strlen(path);
    if (dir != NULL)
        size += my_strlen(dir);
    if (size + 2 <= 0)
        return (NULL);
    new = malloc(sizeof(char) * (size + 15));
    new = get_new("~", new, path, dir);
    return (new);
}

void get_host_name(all_t *all)
{
    char *new = malloc(sizeof(char) * my_strlen(all->current) - 12);
    int idx = 1;

    new[0] = '~';
    for (int i = 14; all->current[i] != '\0'; i++) {
        new[idx] = all->current[i];
        idx++;
    }
    new[idx] = '\0';
    free(all->current);
    all->current = my_strcpy(new, all->current);
}

void check_home_name(all_t *all)
{
    envlist_t *actual = NULL;

    actual = all->env->first;
    while (actual != NULL) {
        if (my_strcmp(actual->key, "HOME") == 0 &&
        my_strcmp(actual->value, "/home/mathilde") == 0) {
            get_host_name(all);
            return;
        }
        if (actual->next == NULL)
            break;
        actual = actual->next;
    }
}