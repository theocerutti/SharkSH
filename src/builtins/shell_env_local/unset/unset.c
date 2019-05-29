/*
** EPITECH PROJECT, 2019
** unset
** File description:
** unset
*/

#include "exec.h"

int unset_shell_var(list_t *shell_var_list, char *key)
{
    node_t *tmp = *shell_var_list;

    for (int pos = 0; tmp != NULL; pos++) {
        if (!strncmp(tmp->var.key, key, strlen(tmp->var.key))) {
            pop_index(shell_var_list, pos);
            return (SUCCESS);
        }
        tmp = tmp->next;
    }
    return (FAILURE);
}

void unset(all_t *all)
{
    if (all->args[1] == NULL) {
        all->exit_code = 1;
        fprintf(stderr, "unset: Too few arguments.\n");
        return;
    }
    for (int i = 1; all->args[i] != NULL; i++) {
        unset_shell_var(&all->shell_var, all->args[i]);
    }
}