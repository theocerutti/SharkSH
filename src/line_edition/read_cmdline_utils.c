/*
** EPITECH PROJECT, 2019
** read_cmdline_utils
** File description:
** read_cmdline_utils
*/

#include "exec.h"

void move_cur_right(char *cap_right, int nb_time)
{
    if (nb_time > 0) {
        for (int i = 0; i < nb_time; i++)
            exec_cap(cap_right);
    }
}

void move_cur_left(char *cap_left, int nb_time)
{
    if (nb_time > 0) {
        for (int i = 0; i < nb_time; i++)
            exec_cap(cap_left);
    }
}

void redisplay_cmdline(all_t *all, cmdline_t *cline)
{
    exec_cap(cline->caps.save_curs);
    exec_cap(cline->caps.clear_line);
    display_input_line(all);
    my_putstr(cline->line);
    exec_cap(cline->caps.restore_save_curs);
}

void clear_cmdline(all_t *all, cmdline_t *cline)
{
    exec_cap(cline->caps.clear_line);
    display_input_line(all);
    for (int i = 0; i < BUF_CMD; i++)
        cline->line[i] = '\0';
    cline->index = 0;
    cline->nb_chars = 0;
    cline->c = 0;
}