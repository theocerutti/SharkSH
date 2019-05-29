/*
** EPITECH PROJECT, 2019
** linked_list manipulator sort
** File description:
** linked_list manipulator sort
*/

#include "exec.h"

static int is_alphabetically_lower(char *s1, char *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] < s2[i]) {
            return (TRUE);
        } else if (s1[i] > s2[i])
            return (FALSE);
    }
    return (FALSE);
}

static void swap_elem_alpha(list_t *list)
{
    node_t *tmp = *list;
    node_t *tmp2 = NULL;
    local_t tmp_var;

    while (tmp != NULL) {
        tmp2 = tmp->next;
        if (tmp2 != NULL &&
        is_alphabetically_lower(tmp2->var.key, tmp->var.key)) {
            tmp_var = tmp->var;
            tmp->var = tmp2->var;
            tmp2->var = tmp_var;
        }
        tmp = tmp->next;
    }
}

void sort_alphanum(list_t *list)
{
    node_t *tmp = *list;

    while (tmp != NULL) {
        swap_elem_alpha(list);
        tmp = tmp->next;
    }
}

void print_list(list_t *list)
{
    node_t *tmp = *list;

    while (tmp != NULL) {
        printf("%s: %s\n", (tmp->var.key) ? tmp->var.key: "(null)",
        (tmp->var.value) ? tmp->var.value: "(null)");
        tmp = tmp->next;
    }
}