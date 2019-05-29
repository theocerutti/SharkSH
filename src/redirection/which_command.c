/*
** EPITECH PROJECT, 2019
** which_command
** File description:
** which_command
*/

#include "exec.h"
#include <dirent.h>

void execute_right_comma(tree_t *t, char **e, all_t *a, int *f)
{
    f[1] = 1;
    if (t->right->str[0] != '<' && t->right->str[0] != ';' &&
    t->right->str[0] != '|' && t->right->str[0] != '>' &&
    t->right->str[0] != '&') {
        if (t->right->par == 1 && t->right->next == 1)
            f[1] = a->fd_parenth;
        else if (t->right->par == 1 && t->right->next == 2)
            f[1] = open(a->file, O_RDWR | O_APPEND);
        if (t->right->path != NULL || (t->right->args != NULL &&
        is_builtin(a, t->right->args[0]) == 0)) choose_exec(a, e, t->right, f);
        else if (t->right->args != NULL) {
            affich_not_found(t->right->args[0]);
            a->exit_code = 1;
            t->success = 1;
        }
    } else execute_tree(t->right, e, a);
}

void execute_semi_colon(tree_t *t, char **e, all_t *a)
{
    int *fd = malloc(sizeof(int) * 2);

    fd[0] = 0;
    fd[1] = 1;
    t->success = 0;
    if (t->left->str[0] != '<' && t->left->str[0] != ';' && t->left->str[0] !=
    '|' && t->left->str[0] != '>' && t->left->str[0] != '&') {
        if (t->left->par == 1 && t->left->next == 1) fd[1] = a->fd_parenth;
        else if (t->left->par == 1 && t->left->next == 2)
            fd[1] = open(a->file, O_RDWR | O_APPEND);
        if (t->left->path != NULL ||
        is_builtin(a, t->left->args[0]) == 0) choose_exec(a, e, t->left, fd);
        else {
            affich_not_found(t->left->args[0]);
            a->exit_code = 1;
            t->success = 1;
        }
    } else execute_tree(t->left, e, a);
    if (t->right != NULL && t->right->str != NULL && t->right->str[0] != '\0')
        execute_right_comma(t, e, a, fd);
}

void execute_pipe_right(tree_t *tr, char **env, all_t *al)
{
    if (tr->right->str[0] != '<' && tr->right->str[0] != ';' &&
    tr->right->str[0] != '|' && tr->right->str[0] != '>' &&
    tr->right->str[0] != '&') {
        if (tr->fd[0] != 84) {
            tr->right->fd[0] = tr->fd[0];
            tr->right->fd[1] = tr->fd[1];
        }
        if (tr->right->path != NULL ||
        is_builtin(al, tr->right->args[0]) == 0)
            choose_pipe_exec(tr->right, env, al, 1);
        else {
            affich_not_found(tr->right->args[0]);
            al->exit_code = 1;
            tr->success = 1;
        }
    } else
        execute_tree(tr->right, env, al);
}

void execute_tree_pipe(tree_t *t, char **env, all_t *al)
{
    t->success = 0;
    if (t->left->str[0] != '<' && t->left->str[0] != ';' &&
    t->left->str[0] != '|' && t->left->str[0] != '>' &&
    t->left->str[0] != '&') {
        if (t->left->path != NULL ||
        is_builtin(al, t->left->args[0]) == 0) {
            choose_pipe_exec(t->left, env, al, 0);
        } else {
            affich_not_found(t->left->args[0]);
            al->exit_code = 1;
            t->success = 1;
        }
    } else {
        if (t->left->str[0] == '<') al->fd_redir = 100;
        execute_tree(t->left, env, al);
    }
    if (t->right != NULL && t->right->str != NULL && t->right->str[0] != '\0')
        execute_pipe_right(t, env, al);
}