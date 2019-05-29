/*
** EPITECH PROJECT, 2019
** history changes the cmd
** File description:
** sharkSH
*/

#include "exec.h"

void include_stock_cmd(all_t *all, int *beg_end, int index)
{
    char *save = my_strcpy_auto(all->input);
    char *save2 = my_strcpy_auto(all->input);

    save[beg_end[0]] = '\0';
    save = my_concat(save, (char *)all->history.vector[index]);
    save2 += (beg_end[1] + 1);
    all->input = my_concat(save, save2);
    free(save);
}

void exec_command_x(char *stock, all_t *all, int *beg_end)
{
    int num = atoi(stock);
    int index_cmd = -1;

    for (int i = 0; i < all->history.size; i += 3)
        if (num == (int)all->history.vector[i])
            index_cmd = i;
    if (num == 0 || index_cmd == -1) {
        my_putstr(stock);
        my_putstr(": Event not found.\n");
        all->exit_code = 1;
    } else
        include_stock_cmd(all, beg_end, index_cmd + 2);
}

void exec_same_cmd(char *stock, all_t *all, int *beg_end)
{
    int index_cmd = -1;

    for (int i = 2; i < all->history.size; i += 3)
        if (strncmp(stock, (char *)all->history.vector[i], strlen(stock)) == 0)
            index_cmd = i;
    if (index_cmd == -1) {
        my_putstr(stock);
        my_putstr(": Event not found.\n");
        all->exit_code = 1;
    } else
        include_stock_cmd(all, beg_end, index_cmd);
}