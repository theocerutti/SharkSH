/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** cd src file Antoine Maillard
*/

#include "exec.h"

void go_on_pos(char **env, int i, int beg)
{
    char *new_dir = NULL;
    int len = 0;

    for (int w = beg; env[i][w] != '\0'; w++, len++);
    new_dir = malloc(len + 1);
    new_dir[len] = '\0';
    for (int w = beg, x = 0; env[i][w] != '\0'; w++, x++) {
        new_dir[x] = env[i][w];
        new_dir[x + 1] = '\0';
    }
    chdir(new_dir);
    free(new_dir);
}

void cd_home(char **env)
{
    int len;

    for (int i = 0; env[i] != NULL; i++) {
        for (len = 0; env[i][len] != '\0'; len++);
        if (len > 4 && env[i][0] == 'H' && env[i][1] == 'O' && \
        env[i][2] == 'M' && env[i][3] == 'E' && env[i][4] == '=')
            go_on_pos(env, i, 5);
    }
}