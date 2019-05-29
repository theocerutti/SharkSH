/*
** EPITECH PROJECT, 2019
** execute
** File description:
** eecute
*/

#include "exec.h"

void permission_denied(char *str, int ex)
{
    if (ex == -1) {
        my_puterror(str);
        my_puterror(": Permission denied.\n");
    }
}

void prepare_exec2(int fk, all_t *all, int *fd)
{
    int status;

    if ((fd[1] == 1 || all->is_pipe == 0)) {
        waitpid(fk, &status, 0);
        if (status != 0) {
            all->success = 1;
            all->exit_code = 2;
        }
        segfault_errors(status, all);
    }
    if (fd[1] != 1) close(fd[1]);
}

void prepare_exec(tree_t *tree, all_t *all, char **env, int *fd)
{
    int fk = 0;
    int ex = 0;

    fk = fork();
    if (fk == 0) {
        if (fd[0] != 0) dup2(fd[0], STDIN_FILENO);
        if (fd[1] != 1) dup2(fd[1], STDOUT_FILENO);
        if (fd[0] != 0) close(fd[0]);
        ex = execve(tree->path, tree->args, env);
        all->success = 1;
        all->exit_code = 1;
        permission_denied(tree->args[0], ex);
    } else
        prepare_exec2(fk, all, fd);
    if (fk == 0) exit(0);
}

void dup_close(int *fd)
{
    if (fd[2] == 55)
        dup2(fd[0], 0);
    else
        close(fd[0]);
    if (fd[2] != 84 && fd[2] != 55)
        dup2(fd[1], 1);
}

void execute_redirect(char *path, char **args, all_t *all, int *fd)
{
    int status = 0;

    if (do_builtin_redirect(path, args, all, fd)) return;
    if ((all->ppid = fork()) == 0) {
        dup_close(fd);
        all->ex = execve(path, args, all->ev_exec);
        all->exit_code = 1;
        permission_denied(args[0], all->ex);
        all->success = 1;
    } else {
        if (fd[2] != 55)
            close(fd[1]);
        if (fd[2] == 84 || fd[2] == 10)
            dup2(fd[0], 0);
        else {
            waitpid(all->ppid, &status, 0);
            segfault_errors(status, all);
        }
    }
    if (all->ppid == 0) exit(0);
}