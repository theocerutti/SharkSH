/*
** EPITECH PROJECT, 2019
** read_cmdline_command
** File description:
** readcmdline_command
*/

#include "exec.h"

int ctrl_f_move_right(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index < cline->nb_chars) {
        move_cur_right(cline->caps.ar_right, 1);
        cline->index += 1;
    }
    return (0);
}

int ctrl_k_cut_line_right(all_t *all, cmdline_t *cline)
{
    for (int i = cline->index; i < BUF_CMD; i++)
        cline->line[i] = '\0';
    cline->nb_chars = cline->index;
    redisplay_cmdline(all, cline);
    return (0);
}

int ctrl_w_cut_line_left(all_t *all, cmdline_t *cline)
{
    for (int i = 0; i < cline->index; i++)
        delete_index_char(cline->line, 0);
    cline->nb_chars = cline->index;
    redisplay_cmdline(all, cline);
    move_cur_left(cline->caps.ar_left, cline->index);
    cline->index = 0;
    return (0);
}

int ctrl_t_transpose_char(all_t *all, cmdline_t *cline)
{
    char tmp_transpose = 0;

    if (cline->index > 0 && cline->index < cline->nb_chars) {
        tmp_transpose = cline->line[cline->index - 1];
        cline->line[cline->index - 1] = cline->line[cline->index];
        cline->line[cline->index] = tmp_transpose;
        redisplay_cmdline(all, cline);
        move_cur_right(cline->caps.ar_right, 1);
        cline->index++;
    }
    return (0);
}