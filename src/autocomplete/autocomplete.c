/*
** EPITECH PROJECT, 2019
** autocompletion
** File description:
** SarkSH
*/

#include "exec.h"
#include <termcap.h>

void change_cmd_auto_spe(all_t *all, cmdline_t *cline)
{
    int save = strlen(cline->line);

    restore_cursor_position(all, cline);
    if (cline->c == K_ENTER) {
        cline->line = update_cline(all, cline);
        cline->index = strlen(cline->line);
        cline->nb_chars = strlen(cline->line);
        redisplay_cmdline(all, cline);
        for (int i = 0; i < cline->nb_chars - save; i++)
            exec_cap(cline->caps.ar_right);
    }
    exec_cap(cline->caps.clear_bottom_screen);
    exec_cap(cline->caps.show_cursor);
}

void choose_new_command(all_t *all, cmdline_t *cline)
{
    kkey_t arrow[] = {{K_UP, up_arrow}, {K_DOWN, down_arrow},
    {K_RIGHT, right_arrow}, {K_LEFT, left_arrow}, {K_TAB, right_arrow}};

    exec_cap(cline->caps.hide_cursor);
    print_complete(all);
    while (cline->c != K_ENTER && cline->c != K_SUPR) {
        cline->c = 0;
        read(STDIN_FILENO, &cline->c, sizeof(int));
        act_for_new_cmd(arrow, all, cline);
    }
    change_cmd_auto_spe(all, cline);
}

void print_complete(all_t *all)
{
    int nb_space = 0;

    all->left_decal = 0;
    all->up_decal = 1;
    my_putstr("\n");
    for (int i = 0; i < all->complete.size; i++)
        prepare_save_cursor(i, all, nb_space);
}

void change_cmd_auto(all_t *all, cmdline_t *cline)
{
    int save = strlen(cline->line);

    cline->line = update_cline(all, cline);
    cline->nb_chars = strlen(cline->line);
    cline->index = strlen(cline->line);
    redisplay_cmdline(all, cline);
    for (int i = 0; i < cline->nb_chars - save; i++)
        exec_cap(cline->caps.ar_right);
}

void autocomplete(all_t *all, cmdline_t *cline)
{
    exec_cap(cline->caps.save_curs);
    all->index_comp = 0;
    if (all->complete.size == 1) {
        change_cmd_auto(all, cline);
    } else if (all->complete.size > 1 && all->complete.size < 150)
        choose_new_command(all, cline);
}