/*
** EPITECH PROJECT, 2019
** exec
** File description:
** exec
*/

#include "exec.h"

void execv2(all_t *all, char **env, tree_t *tree, int *fd)
{
    if (is_builtin(all, tree->args[0]) != 0) {
        prepare_exec(tree, all, env, fd);
    } else {
        fd_out = fd[1];
        my_builtin(all, tree->args[0], tree->args);
        if (fd[1] != 1) close(fd[1]);
        fd_out = 1;
    }
}