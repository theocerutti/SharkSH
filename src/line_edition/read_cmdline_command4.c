/*
** EPITECH PROJECT, 2019
** read_cmdline_command
** File description:
** readcmdline_command
*/

#include "exec.h"

int delete(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->index != cline->nb_chars) {
        delete_index_char(cline->line, cline->index);
        redisplay_cmdline(all, cline);
        if (cline->nb_chars != 0)
            cline->nb_chars -= 1;
    }
    return (0);
}

int insert_char(all_t *all, cmdline_t *cline)
{
    (void)all;
    if (cline->nb_chars >= cline->size_alloc) {
        cline->size_alloc *= 4;
        cline->line = realloc(cline->line, cline->size_alloc);
    }
    insert_char_line(cline->line, cline->index, cline->c);
    cline->nb_chars++;
    cline->index++;
    move_cur_left(cline->caps.ar_right, 1);
    redisplay_cmdline(all, cline);
    return (0);
}

int tab_print_dir(all_t *all, cmdline_t *cline)
{
    int charac = 0;

    for (int i = 0; cline->line[i] != '\0'; i++)
        if (cline->line[i] != ' ')
            charac += 1;
    if (strlen(cline->line) > 0 && charac != 0) {
        get_command_autocomp(all, cline);
        autocomplete(all, cline);
    }
    return (0);
}

int ctrl_l_clear_scr(all_t *all, cmdline_t *cline)
{
    exec_cap(cline->caps.clear_scr);
    display_input_line(all);
    my_putstr(cline->line);
    (void)all;
    return (0);
}

int ctrl_c_sigint(all_t *all, cmdline_t *cline)
{
    (void)all;
    (void)cline;
    if (isatty(0))
        printf("exit\n");
    tcsetattr(0, TCSANOW, &cline->oldterm);
    exit(130);
}