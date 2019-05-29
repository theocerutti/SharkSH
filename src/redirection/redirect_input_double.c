/*
** EPITECH PROJECT, 2019
** redirection_input_db
** File description:
** redirect_input_db
*/

#include "exec.h"

static char *get_input_redirection(char *command)
{
    char *str = NULL;
    size_t n = 0;
    int len = 0;
    int ret = 0;
    char *input = NULL;

    my_putstr("? ");
    if ((ret = getline(&str, &n, stdin)) == -1)
        return (NULL);
    while (strncmp(str, command, strlen(command))) {
        if (input == NULL) input = my_strcpy_auto(str);
        else input = my_strcat(input, str);
        my_putstr("? ");
        if ((ret = getline(&str, &n, stdin)) == -1)
            return (NULL);
    }
    len = strlen(input);
    if (input[len - 1] == '\n')
        input[len - 1] = '\0';
    return (input);
}

static int write_in_file(char *str, char *file)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int out = open(file, O_CREAT | O_WRONLY | O_TRUNC, mode);
    int save_out = dup(STDOUT_FILENO);

    dup2(out, STDOUT_FILENO);
    my_putstr(str);
    my_putstr("\n");
    close(out);
    dup2(save_out, STDOUT_FILENO);
    close(save_out);
    return (0);
}

int exec_redirection_db(tree_t *tree, all_t *all)
{
    char *input = get_input_redirection(tree->right->str);
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int out = STDIN_FILENO;
    int save_out = dup(STDIN_FILENO);

    write_in_file(input, "src/redirection/.tmp_redir_db");
    out = open("src/redirection/.tmp_redir_db", O_RDONLY, mode);
    dup2(out, STDIN_FILENO);
    all->args = tree->left->args;
    execute_program(tree->left->path, all, 0, 0);
    close(out);
    dup2(save_out, STDIN_FILENO);
    close(save_out);
    remove("src/redirection/.tmp_redir_db");
    return (0);
}