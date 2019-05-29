/*
** EPITECH PROJECT, 2019
** restore the cursor position
** File description:
** sharksh auto
*/

#include "exec.h"

void act_for_new_cmd(kkey_t *arrow, all_t *all, cmdline_t *cline)
{
    for (int i = 0; i < 5; i++)
        if (arrow[i].key_id == cline->c) {
            arrow[i].pressed(all, cline);
            restore_cursor_position(all, cline);
            print_complete(all);
            break;
        }
}

void decal_cursor_on_good_way(all_t *all, cmdline_t *cline, int len)
{
    if (all->left_decal > len) {
        for (int i = 0; i < all->left_decal -
        (int)(len + strlen(cline->line) + 2); i++)
            exec_cap(cline->caps.ar_left);
    } else if (all->left_decal < len)
        for (int i = 0; i < (int)(len + strlen(cline->line) + 2) -
        all->left_decal; i++)
            exec_cap(cline->caps.ar_right);
}

void restore_cursor_position(all_t *all, cmdline_t *cline)
{
    int len = 0;
    envlist_t *ev = all->env->first;

    if (all->env == NULL)
        return;
    while (ev != NULL) {
        if (my_strcmp_cd(ev->key, "PWD") == 1) {
            len = strlen(ev->value);
            break;
        }
        ev = ev->next;
    }
    decal_cursor_on_good_way(all, cline, len);
    for (int i = 0; i < all->up_decal; i++)
        exec_cap(cline->caps.ar_up);
}

void prepare_save_cursor(int i, all_t *all, int nb_space)
{
    if (i % 5 == 0 && i != 0 && i != all->complete.size - 1) {
        my_putstr("\n");
        all->left_decal = 0;
        all->up_decal += 1;
    }
    if (i == all->index_comp)
        my_putstr("\e[7m");
    my_putstr((char *)all->complete.vector[i]);
    all->left_decal += strlen((char *)all->complete.vector[i]);
    if (i == all->index_comp)
        my_putstr("\e[0m");
    nb_space = strlen((char *)all->complete.vector[i]);
    for (int w = 0; w < all->len_bin + 5 - nb_space; w++) {
        my_putstr(" ");
        all->left_decal += 1;
    }
}