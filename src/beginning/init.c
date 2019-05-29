/*
** EPITECH PROJECT, 2019
** init
** File description:
** init
*/

#include "exec.h"

int fd_out;

void init2(all_t *all)
{
    all->args = process_globings(all->args);
    all->args = manage_alias(all->args, all);
    for (int elem = 0; builtins[elem].name != NULL; elem++) {
        if (my_strcmp_cd(all->args[0], builtins[elem].name)) {
            builtins[elem].exec(all);
            return;
        }
    }
    quotes(all);
    existent_func(all);
}

void display_input_line(all_t *all)
{
    char *directory = NULL;

    all->exit_code = 0;
    all->success = 0;
    if (isatty(0)) {
        directory = getcwd(NULL, 0);
        change_pwd_env(directory, all->ev_exec);
        if (directory == NULL)
            my_putstr("$> ");
        else {
            my_putstr("\033[34m\033[1m");
            my_putstr(directory);
            my_putstr("\033[0m> ");
            free(directory);
        }
    }
}

int get_input(all_t *all, int check)
{
    int ret = 0;
    size_t n = 0;

    if (isatty(0)) {
        if (check == 0) all->input = read_cmdline(all);
        if (all->input[0] == '\n')
            return (ERROR);
    } else {
        ret = getline(&all->input, &n, stdin);
        if (ret == 1)
            return (0);
        else if (ret == -1)
            exit(all->exit_code);
        if (all->input[0] == '\n')
            return (ERROR);
    }
    if (error_input_match(all->input) == 84 || \
    error_parenthesis(all->input) == 84)
        return (ERROR);
    return (0);
}

void exec_command(all_t *all)
{
    for (int i = 0; all->input[i] != '\0'; i++)
        if (REDIRECTION(all->input[i]) ||
        ((all->input[i] == '\'' || all->input[i] == '\"')
        && my_strcmp(all->args[0], "alias") == 1)) {
            with_pipe(all);
            return;
        }
    if (all->args[0] != NULL)
        init2(all);
}

int init(all_t *all, char *line, int check)
{
    display_input_line(all);
    if (get_input(all, check) == ERROR) {
        all->exit_code = 1;
        return (1);
    }
    line = manage_back_line(all, line, 0, 0);
    for (int i = 0; all->input[i] != '\0'; i++)
        if (all->input[i] == '\n') all->input[i] = '\0';
    if (check_history(all))
        return (all->exit_code);
    get_history(all);
    all->args = args_in_tab(all->input);
    if (all->args == NULL) all->exit_code = 1;
    if (all->args == NULL) return (1);
    exec_command(all);
    if (line != NULL) all->input = my_strcpy(line, all->input);
    if (line != NULL) init(all, NULL, 1);
    return (all->exit_code);
}