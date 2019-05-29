/*
** EPITECH PROJECT, 2019
** read_cmdline_command
** File description:
** readcmdline_command
*/

#include "exec.h"

int ctrl_a_begin_line(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index > 0) {
        move_cur_left(cline->caps.ar_left, cline->index);
        cline->index = 0;
    }
    return (0);
}

int ctrl_b_move_left(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index > 0) {
        move_cur_left(cline->caps.ar_left, 1);
        cline->index -= 1;
    }
    return (0);
}

int ctrl_e_end_line(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index < cline->nb_chars) {
        move_cur_right(cline->caps.ar_right, cline->nb_chars - cline->index);
        cline->index = cline->nb_chars;
    }
    return (0);
}

int ctrl_j_new_line(all_t *all, cmdline_t *cline)
{
    (void)all;
    (void)cline;
    return (QUIT_CMD);
}

int ctrl_u_clear_line(all_t *all, cmdline_t *cline)
{
    clear_cmdline(all, cline);
    return (0);
}