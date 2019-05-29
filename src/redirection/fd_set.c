/*
** EPITECH PROJECT, 2019
** fd_set
** File description:
** fd_set
*/

#include "exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void choose_exec(all_t *all, char **env, tree_t *tree, int *fd)
{
    (void)env;
    all->is_pipe = 0;
    tree->args = process_globings(tree->args);
    execv2(all, env, tree, fd);
    all->fd_parenth = open(all->par_file, O_RDWR | O_APPEND);
}

void set_semi_colon(tree_t *tree)
{
    tree->left->fd[0] = 0;
    tree->left->fd[1] = 1;
    tree->right->fd[0] = 0;
    tree->right->fd[1] = 1;
}

void set_simple_right(tree_t *tree)
{
    int fd = 0;

    fd = open(tree->right->args[0], O_RDONLY);
    if (fd == -1 && opendir(tree->right->args[0]) == NULL)
        fd = -1;
    else if (fd == -1)
        fd = -2;
    tree->left->fd[0] = fd;
    tree->left->fd[1] = 1;
    tree->right->fd[0] = 0;
    tree->right->fd[1] = fd;
}

void set_simple_left(tree_t *tree)
{
    int fd = 0;

    fd = open(tree->right->args[0], O_RDONLY);
    if (fd == -1 && opendir(tree->right->args[0]) == NULL)
        fd = -1;
    else if (fd == -1)
        fd = -2;
    tree->left->fd[0] = fd;
    tree->left->fd[1] = 1;
    tree->right->fd[0] = 0;
    tree->right->fd[1] = fd;
}

void nothing(tree_t *tree)
{
    (void)tree;
    return;
}