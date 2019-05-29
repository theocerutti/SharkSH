/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** cd src file Antoine Maillard
*/

#include "exec.h"

void change_pwd_env(char *str, char **env)
{
    int len;

    for (int i = 0; env[i] != NULL; i++) {
        for (len = 0; env[i][len] != '\0'; len++);
        if (len > 3 && env[i][0] == 'P' && env[i][1] == 'W'
        && env[i][2] == 'D' && env[i][3] == '=')
            env[i] = concat_env("PWD", str);
    }
}

void cd_move_error(char **env, int *exit_code)
{
    if (is_exist("HOME", env) != -1) {
        printf("~ \n");
    } else {
        fprintf(stderr, ": No such file or directory.\n");
        *exit_code = 1;
    }
}

void cd_move(char **command, char **env, int *exit_code)
{
    if (chdir(command[1]) == -1 && my_strcmp_cd("-", command[1]) == 0 && \
    my_strcmp_cd("~", command[1]) == 0 && \
    my_strcmp_cd("home", command[1]) == 0) {
        direction_error(command[1], exit_code);
    } else {
        if (my_strcmp_cd("-", command[1]) == 1)
            cd_back(env, exit_code);
        if (my_strcmp_cd("~", command[1]) == 1)
            cd_home(env);
        if (my_strcmp_cd("home", command[1]) == 1) {
            cd_home(env);
            cd_move_error(env, exit_code);
        }
    }
}

int parse_cd(char *str, char **env, all_t *all)
{
    char *oldpwd = NULL;
    char **command = NULL;
    int did = 0;
    int exist = is_exist("OLDPWD", env);

    oldpwd = getcwd(oldpwd, 0);
    command = str_word_array(str);
    if (my_strcmp_cd("cd", command[0]) == 1 && count_word(str) == 2) {
        cd_move(command, env, &all->exit_code);
        did = 1;
    } else if (my_strcmp_cd("cd", command[0]) == 1 && count_word(str) == 1) {
        cd_home(env);
        did = 1;
    } else
        cd_error(command, &did, &all->exit_code);
    if (exist != -1)
        env[exist] = concat_env("OLDPWD", oldpwd);
    else
        prepa_set_env(env, oldpwd, &all->exit_code);
    return (did);
}
