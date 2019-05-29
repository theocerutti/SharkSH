/*
** EPITECH PROJECT, 2019
** check_functions
** File description:
** check if is function or not
*/

#include "exec.h"
#include <signal.h>

void affich(all_t *all)
{
    my_puterror(all->args[0]);
    my_puterror(": Command not found.\n");
    all->exit_code = 1;
}

void existent_func(all_t *all)
{
    char **path = get_exec_path(all);
    char *exec = NULL;

    if (path[0] == NULL) {
        affich(all);
        return;
    }
    if (access(all->args[0], F_OK) == 0) {
        execute_program(all->args[0], all, 0, 0);
        return;
    }
    for (int i = 0; path[i] != NULL; i++) {
        exec = my_strcat_path(path[i], all->args[0]);
        if (access(exec, F_OK) == 0) {
            execute_program(exec, all, 0, 0);
            return;
        }
        free(exec);
    }
    affich(all);
}

void affich_not_found(char *str)
{
    my_puterror(str);
    my_puterror(": Command not found.\n");
}

char *valid_path(char **str, all_t *all)
{
    char **path = get_exec_path(all);
    char *exec = NULL;

    if (path[0] == NULL) {
        return (NULL);
    }
    if (access(str[0], F_OK) == 0) {
        return (str[0]);
    }
    for (int i = 0; path[i] != NULL; i++) {
        exec = my_strcat_path(path[i], str[0]);
        if (access(exec, F_OK) == 0) {
            return (exec);
        }
        free(exec);
    }
    return (NULL);
}