/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** src cd back Antoine Maillard
*/

#include "exec.h"

void prepa_set_env(char **env, char *oldpwd, int *exit_code)
{
    int did = 0;
    char str[] = "setenv OLDPWD";
    char *used = concat_space(str, oldpwd);
    char **command = str_word_array(used);

    set_env(command, env, &did, exit_code);
}

int cd_back(char **env, int *exit_code)
{
    int exist = is_exist("OLDPWD", env);

    if (exist == -1) {
        fprintf(stderr, ": No such file or directory.\n");
        *exit_code = 1;
        return (0);
    } else
        go_on_pos(env, exist, 7);
    return (0);
}
