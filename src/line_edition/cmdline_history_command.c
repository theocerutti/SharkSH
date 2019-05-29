/*
** EPITECH PROJECT, 2019
** history_cmdline_command
** File description:
** history_cmdline_command
*/

#include "exec.h"

void replace_str_cmdline(all_t *all, cmdline_t *cline, char *command)
{
    int len_command = my_strlen(command);

    clear_cmdline(all, cline);
    my_putstr(command);
    strcpy(cline->line, command);
    cline->index = len_command;
    cline->nb_chars = len_command;
}

int cmdline_history_up(all_t *all, cmdline_t *cline)
{
    char *command = get_history_cmd_up(all, cline);

    if (command != NULL)
        replace_str_cmdline(all, cline, command);
    return (0);
}

int cmdline_history_down(all_t *all, cmdline_t *cline)
{
    char *command = get_history_cmd_down(all, cline);

    if (command != NULL)
        replace_str_cmdline(all, cline, command);
    return (0);
}