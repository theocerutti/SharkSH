/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** setenv src file Antoine Maillard
*/

#include "exec.h"

void set_env(char **command, char **env, int *did, int *exit_code)
{
    int len;

    *did = 1;
    for (len = 0; command[len] != NULL; len++);
    if (len < 2)
        print_env(env, did);
    if (len == 3 || len == 2) {
        check_set_new(command, env, len, exit_code);
    } else if (len > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        *exit_code = 1;
    }
}

void create_new(char **command, char **env, int const len)
{
    int len_e;

    my_realloc(env);
    for (len_e = 0; env[len_e] != NULL; len_e++);
    if (len == 2)
        env[len_e] = concat_env(command[1], "");
    else
        env[len_e] = concat_env(command[1], command[2]);
    env[len_e + 1] = NULL;
}

void modify_or_add(char **command, char **env, int const len, int i)
{
    if (len == 2)
        env[i] = concat_env(command[1], "");
    else if (command[2][0] == '$') {
        env[i] = concat_env_add(env[i], command[2]);
    } else
        env[i] = concat_env(command[1], command[2]);
}

int check_non_alpha_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') \
        && (str[i] < '0' || str[i] > '9'))
            return (1);
    return (0);
}

int check_set_new(char **command, char **env, int const len, int *exit_code)
{
    int exist = 0;

    if ((command[1][0] < 'A' || command[1][0] > 'Z') && \
    (command[1][0] < 'a' || command[1][0] > 'z')) {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        *exit_code = 1;
    } else if (check_non_alpha_num(command[1]) == 1) {
        fprintf(stderr,
        "setenv: Variable name must contain alphanumeric characters.\n");
        *exit_code = 1;
    } else {
        exist = is_exist(command[1], env);
        if (exist == -1)
            create_new(command, env, len);
        else
            modify_or_add(command, env, len, exist);
    }
    return (0);
}