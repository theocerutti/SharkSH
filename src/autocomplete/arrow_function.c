/*
** EPITECH PROJECT, 2019
** arrow functions
** File description:
** SharkSH
*/

#include "exec.h"

int up_arrow(all_t *all, cmdline_t *cline)
{
    (void)cline;
    if (all->index_comp - 5 > 0)
        all->index_comp -= 5;
    return (0);
}

int down_arrow(all_t *all, cmdline_t *cline)
{
    (void)cline;
    if (all->index_comp + 5 <= all->complete.size - 1)
        all->index_comp += 5;
    return (0);
}

int left_arrow(all_t *all, cmdline_t *cline)
{
    (void)cline;
    if (all->index_comp > 0)
        all->index_comp -= 1;
    return (0);
}

int right_arrow(all_t *all, cmdline_t *cline)
{
    (void)cline;
    if (all->index_comp < all->complete.size - 1)
        all->index_comp += 1;
    return (0);
}