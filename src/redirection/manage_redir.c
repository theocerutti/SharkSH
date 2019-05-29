/*
** EPITECH PROJECT, 2019
** manage_redir
** File description:
** manage redirection
*/

#include "exec.h"

char *get_tmp(tree_t *tree, char *tmp)
{
    if (tree->right->str[0] == '|') {
        my_puterror("Ambiguous output redirect.\n");
        exit(1);
    } else
        tmp = my_strcpy(tree->right->args[0], tmp);
    return (tmp);
}

void exec_redirect_right(all_t *all, char **env, tree_t *tree, int *fd)
{
    int fd1 = 0;
    char *tmp = NULL;

    (void)all;
    tmp = get_tmp(tree, tmp);
    fd1 = open(tmp, O_RDONLY | O_CREAT,
    S_IRWXU | S_IROTH);
    all->file = my_strcpy(tmp, all->file);
    if (tree->str[1] == '>') fd1 = open(tmp, O_WRONLY | O_APPEND);
    else fd1 = open(tmp, O_WRONLY | O_TRUNC);
    if (tree->left->par == 1) execute_tree(tree->left, env, all);
    if (tree->left->str[0] != '|' && tree->left->par != 1) {
        fd[0] = 0;
        fd[1] = fd1;
        all->is_pipe = 0;
        execv2(all, env, tree->left, fd);
    } else if (tree->left->par != 1) {
        all->set_out = fd1;
        execute_tree(tree->left, env, all);
    }
}

void execute_redirect_right(tree_t *tree, char **env, all_t *all)
{
    int *fd = malloc(sizeof(int) * 2);

    fd[0] = 0;
    fd[1] = 0;
    all->ppid = 0;
    all->ex = 0;
    exec_redirect_right(all, env, tree, fd);
}

void exec_redirect_left(all_t *all, char **env, tree_t *tree, int fd1)
{
    int *fd = malloc(sizeof(int) * 2);

    fd[0] = fd1;
    fd[1] = 1;
    all->ppid = 0;
    all->ex = 0;
    if (all->fd_redir == 100) {
        all->fd_redir = fd[0];
        choose_pipe_exec(tree->left, env, all, 2);
        all->fd_redir = 0;
    } else {
        execv2(all, env, tree->left, fd);
        all->fd_redir = 0;
    }
}

void execute_redirect_left(tree_t *t, char **env, all_t *all)
{
    int fd1 = 0;

    if (t->str[0] == '<' && t->str[1] == '<') exec_redirection_db(t, all);
    if (t->str[0] == '<' && t->str[1] == '<') return;
    if (t->left->str[0] == '<' || t->left->str[0] == ';' ||
    t->left->str[0] == '|' || t->left->str[0] == '>' ||
    t->left->str[0] == '&') execute_tree(t->left, env, all);
    else {
        fd1 = open(t->right->args[0], O_RDONLY);
        if (fd1 == -1 && opendir(t->right->args[0]) == NULL) {
            my_puterror(t->right->args[0]);
            my_puterror(": No such file or directory.\n");
            all->exit_code = 1;
        }
        if (all->exit_code != 1) exec_redirect_left(all, env, t, fd1);
    }
    if (t->right->str[0] == '<' || t->right->str[0] == ';' ||
    t->right->str[0] == '|' || t->right->str[0] == '>' ||
    t->right->str[0] == '&')
        execute_tree(t->right, env, all);
}
