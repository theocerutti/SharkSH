/*
** EPITECH PROJECT, 2019
** print the history
** File description:
** Shark SH
*/

#include "exec.h"

void history(all_t *all)
{
    for (int i = 0; i < all->history.size; i++) {
        printf("     %d", (int)all->history.vector[i]);
        i += 1;
        printf("\t%s", (char *)all->history.vector[i]);
        i += 1;
        printf("\t%s\n", (char *)all->history.vector[i]);
    }
}