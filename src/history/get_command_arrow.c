/*
** EPITECH PROJECT, 2019
** get_command_arrow
** File description:
** get_command_arrow
*/

#include "exec.h"

char *get_history_cmd_up(all_t *all, cmdline_t *cline)
{
    if (all->history.size == 0)
        return (NULL);
    if (cline->history_index > 2) {
        cline->history_index -= 3;
        return ((char *)all->history.vector[cline->history_index]);
    }
    return ((char *)all->history.vector[cline->history_index]);
}

char *get_history_cmd_down(all_t *all, cmdline_t *cline)
{
    if (all->history.size == 0)
        return (NULL);
    if (cline->history_index >= all->history.size - 1) {
        cline->history_index = all->history.size - 1 + 3;
        return ("");
    }
    if (cline->history_index == 0) {
        cline->history_index += 2;
        return ((char *)all->history.vector[cline->history_index]);
    }
    if (cline->history_index >= 2) {
        cline->history_index += 3;
        return ((char *)all->history.vector[cline->history_index]);
    }
    return ((char *)all->history.vector[cline->history_index]);
}