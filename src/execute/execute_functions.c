/*
** EPITECH PROJECT, 2019
** execute_functions
** File description:
** execute functions
*/

#include "exec.h"

char **cat_exec_path(char *str)
{
    char *to_cat = NULL;
    int idx = 0;
    char **path = NULL;

    to_cat = malloc(sizeof(char) * (my_strlen(str) - 4));
    for (int i = 5; str[i] != '\n' && str[i] != '\0'; i++) {
        to_cat[idx] = str[i];
        idx++;
    }
    to_cat[idx] = '\0';
    path = path_to_word_array(path, to_cat);
    return (path);
}

int check_path(all_t *all)
{
    envlist_t *actual = NULL;

    actual = all->env->first;
    while (actual != NULL) {
        if (my_strcmp(actual->key, "PATH") == 0)
            break;
        if (actual->next == NULL)
            return (1);
        actual = actual->next;
    }
    return (0);
}

char **get_exec_path(all_t *all)
{
    envlist_t *actual = NULL;
    char **path = NULL;

    if (check_path(all) == 1)
        return (all->args);
    actual = all->env->first;
    while (actual != NULL) {
        if (my_strcmp(actual->key, "PATH") == 0)
            break;
        if (actual->next == NULL) {
            path = malloc(sizeof(char *) * 2);
            path[0] = NULL;
            return (path);
        }
        actual = actual->next;
    }
    return (path_to_word_array(path, actual->value));
}

void segfault_errors(int status, all_t *all)
{
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGABRT)
            my_puterror("Abort");
        else if (WTERMSIG(status) == SIGSEGV)
            my_puterror("Segmentation fault");
        else
            my_puterror("Floating exception");
        if (WCOREDUMP(status))
            my_puterror(" (core dumped)\n");
        else
            my_puterror("\n");
        all->exit_code = 1;
    }
    return;
}

void execute_program(char *path, all_t *all, int ppid, int nb)
{
    int status;

    ppid = fork();
    if (ppid == 0) {
        nb = execve(path, all->args, all->ev_exec);
        if (errno == ENOEXEC) {
            my_puterror(all->args[0]);
            my_puterror(": Exec format error. Wrong Architecture.\n");
            all->exit_code = 1;
        } else if (nb == -1) {
            my_puterror(all->args[0]);
            my_puterror(": Permission denied.\n");
            all->exit_code = 1;
        }
    } else {
        waitpid(ppid, &status, 0);
        segfault_errors(status, all);
    }
}