/*
** EPITECH PROJECT, 2019
** functions to modify the env
** File description:
** oldpwd 42sh
*/

#include "exec.h"

void change_old_pwd_value(char *value, char **env)
{
    int index = -1;

    if ((index = is_exist("OLDPWD", env)) != -1) {
        env[index] += strlen("OLDPWD=");
        value = strcpy(value, env[index]);
        env[index] -= strlen("OLDPWD=");
    }
}

void change_pwd_value_list(char *value, char **env)
{
    int index = -1;

    if ((index = is_exist("PWD", env)) != -1) {
        env[index] += strlen("PWD=");
        value = strcpy(value, env[index]);
        env[index] -= strlen("PWD=");
    }
}