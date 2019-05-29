/*
** EPITECH PROJECT, 2019
** read_cmdline_command
** File description:
** readcmdline_command
*/

#include "exec.h"

int move_left(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index > 0) {
        move_cur_left(cline->caps.ar_left, 1);
        cline->index -= 1;
    }
    return (0);
}

int move_right(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index < cline->nb_chars) {
        move_cur_right(cline->caps.ar_right, 1);
        cline->index += 1;
    }
    return (0);
}

int backspace(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index > 0) {
        cline->index -= 1;
        delete_index_char(cline->line, cline->index);
        redisplay_cmdline(all, cline);
        exec_cap(cline->caps.ar_left);
        if (cline->nb_chars != 0)
            cline->nb_chars -= 1;
    }
    return (0);
}