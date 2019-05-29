/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** unsetenv src file Antoine Maillard
*/

#include "exec.h"

void unset_this_var(char **env, int pos)
{
    for (int i = pos; env[i] != NULL; i++)
        env[i] = env[i + 1];
}

int unset_env(char **command, char **env, int *did, int *exit_code)
{
    int exist = 0;
    int len = 0;

    *did = 1;
    for (len = 0; command[len] != NULL; len++);
    if (len == 1) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        *exit_code = 1;
        return (0);
    }
    for (int i = 1; command[i] != NULL; i++)
        if ((exist = is_exist(command[i], env)) != -1)
            unset_this_var(env, exist);
    return (0);
}