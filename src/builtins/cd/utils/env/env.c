/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** env src file Antoine Maillard
*/

#include "exec.h"

int parse_env(char *str, char **env, int *exit_code)
{
    char **command = str_word_array(str);
    int did = 0;

    if (my_strcmp_cd(command[0], "env") == 1)
        print_env(env, &did);
    if (my_strcmp_cd(command[0], "setenv") == 1)
        set_env(command, env, &did, exit_code);
    if (my_strcmp_cd(command[0], "unsetenv") == 1)
        unset_env(command, env, &did, exit_code);
    return (did);
}

void print_env(char **env, int *did)
{
    *did = 1;
    for (int i = 0; env[i] != NULL; i++) {
        printf("%s\n", env[i]);
    }
}

int is_exist(char *var, char **env)
{
    int len_v;
    int len_e;

    for (int i = 0; env[i] != NULL; i++) {
        for (len_e = 0; env[i][len_e] != '\0'; len_e++);
        for (len_v = 0; var[len_v] != '\0'; len_v++);
        for (int w = 0, check = 0; w < len_v && len_e > len_v; w++) {
            if (var[w] == env[i][w])
                check += 1;
            if (var[w + 1] == '\0' && env[i][w + 1] == '=' && check == len_v)
                return (i);
        }
    }
    return (-1);
}