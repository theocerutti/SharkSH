/*
** EPITECH PROJECT, 2019
** set
** File description:
** set
*/

#include "exec.h"

void print_shell_env(all_t *all)
{
    node_t *tmp = all->shell_var;

    printf("_\t%s\n", (all->last_command) ? all->last_command : "");
    while (tmp != NULL) {
        printf("%s\t", (tmp->var.key) ? tmp->var.key : "");
        if (tmp->var.parenthesis == TRUE)
            printf("(");
        printf("%s", (tmp->var.value) ? tmp->var.value : "");
        if (tmp->var.parenthesis == TRUE)
            printf(")");
        printf("\n");
        tmp = tmp->next;
    }
}