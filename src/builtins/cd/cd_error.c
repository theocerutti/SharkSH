/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** cd errors src file Antoine Maillard
*/

#include "exec.h"

void direction_error(char *path, int *exit_code)
{
    DIR *dir = NULL;

    if ((dir = opendir(path)) == NULL && access(path, F_OK) == 0)
        fprintf(stderr, "%s: Not a directory.\n", path);
    else {
        fprintf(stderr, "%s: No such file or directory.\n", path);
    }
    *exit_code = 1;
}

void cd_error(char **command, int *did, int *exit_code)
{
    int len = 0;

    for (len = 0; command[len] != NULL; len++);
    if (my_strcmp_cd("cd", command[0]) == 1 && len > 2) {
        fprintf(stderr, "cd: Too many arguments.\n");
        *did = 1;
        *exit_code = 1;
    }
}
