/*
** EPITECH PROJECT, 2019
** put_default_env
** File description:
** put_default_env
*/

#include "exec.h"

void put_def_variables_env(fenvlist_t *list)
{
    envlist_t *env = NULL;
    struct passwd *pw = getpwuid(getuid());
    char path[] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:";
    char path2[] = "/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";

    list_insert_first(list, "HOME", pw->pw_dir);
    env = list->first;
    list_insert_last(env, "OLDPWD", getcwd(NULL, 0));
    env = env->next;
    list_insert_last(env, "PWD", getcwd(NULL, 0));
    env = env->next;
    list_insert_last(env, "PATH", my_strcat(path, path2));
    env = env->next;
    list_insert_last(env, "TERM", "xterm-256color");
    env = env->next;
    list_insert_last(env, "SHLVL", "2");
}

fenvlist_t *put_default_env(all_t *all)
{
    char **ev_exec = NULL;
    int size = 0;
    fenvlist_t *list = envlist_init();
    envlist_t *env = NULL;

    put_def_variables_env(list);
    env = list->first;
    for (size = 0; env != NULL; size++, env = env->next);
    ev_exec = malloc(sizeof(char *) * (size + 1));
    env = list->first;
    for (int i = 0; env != NULL; i++) {
        ev_exec[i] = malloc(sizeof(char) * (strlen(env->key) +
        strlen(env->value) + 1));
        strcpy(ev_exec[i], env->key);
        strcat(ev_exec[i], env->value);
        env = env->next;
    }
    ev_exec[size] = NULL;
    all->ev_exec = ev_exec;
    return (list);
}