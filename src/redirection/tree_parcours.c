/*
** EPITECH PROJECT, 2019
** tree_parcours
** File description:
** tree_parcours
*/

#include "exec.h"

void second_of_double_pipe(tree_t *t, char **env, all_t *a)
{
    if (t->right->str[0] == '|' || t->right->str[0] == '&')
        execute_tree(t->right, env, a);
    else {
        if (t->par == 1 && t->next == 1) a->fd_double[1] = a->fd_parenth;
        else if (t->par == 1 && t->next == 2)
            a->fd_double[1] = open(a->file, O_RDWR | O_APPEND);
        else a->fd_double[1] = 1;
        a->is_pipe = 0;
        if (t->right->path == NULL && is_builtin(a, t->right->args[0]) == 1) {
            affich_not_found(t->right->args[0]);
            a->exit_code = 1;
            a->success = 1;
        } else {
            a->exit_code = 0;
            execv2(a, env, t->right, a->fd_double);
        }
        t->right->success = a->success;
    }
}

void first_and_or(tree_t *t, all_t *a, int **fd, char **env)
{
    if (t->par == 1 && t->next == 1)
        fd[0][1] = a->fd_parenth;
    else if (t->par == 1 && t->next == 2)
        fd[0][1] = open(a->file, O_RDWR | O_APPEND);
    else
        fd[0][1] = 1;
    a->is_pipe = 0;
    if (t->left->path == NULL && is_builtin(a, t->left->args[0]) == 1) {
        affich_not_found(t->left->args[0]);
        a->exit_code = 1;
        a->success = 1;
    } else
        execv2(a, env, t->left, fd[0]);
    t->left->success = a->success;
}

void execute_double_pipe(tree_t *t, char **env, all_t *all, char op)
{
    int *fd = malloc(sizeof(int) * 2);

    fd[0] = 0;
    if (t->left == NULL || t->left->str == NULL || t->left->str[0] == '\0') {
        all->fd_double[0] = 0;
        second_of_double_pipe(t, env, all);
        return;
    }
    if (t->left->str[0] == '|' || t->left->str[0] == '&' ||
    t->left->str[0] == '<' || t->left->str[0] == '>' ||
    t->left->str[0] == ';') execute_tree(t->left, env, all);
    else
        first_and_or(t, all, &fd, env);
    all->fd_double[0] = fd[0];
    all->fd_double[1] = fd[1];
    if ((t->left->success == 1 && op == '|') || (t->left->success == 0
    && op == '&'))
        second_of_double_pipe(t, env, all);
    all->success = 0;
}

void execute_tree2(tree_t *t, char **e, all_t *a)
{
    if (t->str[0] == '|' && t->str[1] == '|' &&
    operand_in_quote(t->str, "||") == 0)
        execute_double_pipe(t, e, a, '|');
    if (t->str[0] == '&' && t->str[1] == '&' &&
    operand_in_quote(t->str, "&&") == 0)
        execute_double_pipe(t, e, a, '&');
    if (t->str[0] == '|' && t->str[1] != '|' &&
    operand_in_quote(t->str, "|") == 0)
        execute_tree_pipe(t, e, a);
}

void execute_tree(tree_t *t, char **e, all_t *a)
{
    if (t->next != 0) {
        if (t->left != NULL) t->left->next = t->next;
        if (t->right != NULL) t->right->next = t->next;
    }
    if (t->str[0] == ';' && operand_in_quote(t->str, ";") == 0)
        execute_semi_colon(t, e, a);
    else {
        if (t->str[0] == '<' && (operand_in_quote(t->str, "<") == 0 ||
        operand_in_quote(t->str, "<<") == 0))
            execute_redirect_left(t, e, a);
        else if (t->str[0] == '>' && operand_in_quote(t->str, ">") == 0) {
            execute_redirect_right(t, e, a);
            a->set_out = 1;
        }
    }
    execute_tree2(t, e, a);
}