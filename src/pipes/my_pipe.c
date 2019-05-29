/*
** EPITECH PROJECT, 2019
** my_pipe
** File description:
** my_pipe
*/

#include "exec.h"

void display_tree(tree_t *tree)
{
    if (tree->str == NULL)
        return;
    tree->fd[0] = 84;
    if (tree->left != NULL)
        display_tree(tree->left);
    if (tree->right != NULL)
        display_tree(tree->right);
}

int error_input_pipe(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '|')
            return (0);
        if (str[i] == '|') {
            my_puterror("Invalid null command.\n");
            return (84);
        }
    }
    return (84);
}

void init_tree(all_t *all, tree_t *tree)
{
    all->is_pipe = 0;
    all->is_builtin = 0;
    tree->par = 0;
    tree->next = 0;
    remove(all->par_file);
    all->fd_parenth = open(all->par_file,
    O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
    tree->fd[0] = 0;
    tree->fd[1] = 1;
    tree->success = 0;
    all->set_in = 0;
    all->set_out = 1;
    all->fd_double = malloc(sizeof(int) * 2);
    tree->str = my_strcpy(all->input, tree->str);
}

void begin_execute(tree_t *tree, char **envi, all_t *all, int fd[2])
{
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->path != NULL || is_builtin(all, tree->args[0]) == 0)
            execv2(all, envi, tree, fd);
        else if (tree->path == NULL) {
            all->exit_code = 1;
            affich_not_found(tree->args[0]);
        }
    } else
        execute_tree(tree, envi, all);
}

void my_pipe(all_t *all)
{
    tree_t *tree = malloc(sizeof(*tree));
    char **envi = NULL;
    int fd[2] = {0, 1};

    init_tree(all, tree);
    envi = get_array_env(all->ev_exec);
    if (error_input(all->input) == 84 ||
    error_input_pipe(all->input) == 84) {
        all->exit_code = 1;
        return;
    }
    complete_tree(tree, all->input);
    get_args_tree(tree, all);
    display_tree(tree);
    begin_execute(tree, envi, all, fd);
    close(all->fd_parenth);
    remove(all->par_file);
}