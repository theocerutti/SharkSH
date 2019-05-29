/*
** EPITECH PROJECT, 2019
** choose_exec
** File description:
** choose_exec
*/

#include "exec.h"

int is_builtin(all_t *all, char *str)
{
    (void)all;
    for (int elem = 0; builtins[elem].name != NULL; elem++)
        if (my_strcmp_cd(str, builtins[elem].name))
            return (0);
    return (1);
}

char **my_copy_args(char **str, char **src)
{
    int size = 0;

    free(str);
    for (; src[size] != NULL; size++);
    str = malloc(sizeof(char *) * (size + 1));
    for (int i = 0; src[i] != NULL; i++)
        str[i] = my_strcpy(src[i], str[i]);
    str[size] = NULL;
    return (str);
}

int my_builtin(all_t *all, char *str, char **args)
{
    for (int elem = 0; builtins[elem].name != NULL; elem++) {
        if (my_strcmp_cd(str, builtins[elem].name)) {
            all->is_builtin = 1;
            all->args = my_copy_args(all->args, args);
            all->input = my_tab_to_str(args, " ");
            builtins[elem].exec(all);
            return (0);
        }
    }
    all->is_builtin = 0;
    return (1);
}

void choose_pipe_exec(tree_t *tree, char **env, all_t *all, int check)
{
    static int mpipe[2] = {0, 1};
    static int npipe[2] = {0, 1};
    static int alone = 0;

    pipe(npipe);
    if (check == 0 || check == 2) {
        mpipe[1] = npipe[1];
        all->is_pipe = 1;
        if (check == 2) mpipe[0] = all->fd_redir;
        execv2(all, env, tree, mpipe);
        alone = 1;
    } else {
        if (!alone && tree->par == 5) mpipe[0] = open(all->par_file, O_RDONLY);
        alone = 0;
        mpipe[1] = all->set_out;
        if (tree->par == 1) mpipe[1] = open(all->par_file,
        O_WRONLY | O_APPEND);
        execv2(all, env, tree, mpipe);
    }
    all->is_pipe = 0;
    mpipe[0] = npipe[0];
}

int do_builtin_redirect(char *path UNUSED, char **args, all_t *all, int *fd)
{
    if (is_builtin(all, args[0]) == 0) {
        fd_out = fd[1];
        my_builtin(all, args[0], args);
        fd_out = 1;
        return (1);
    }
    return (0);
}