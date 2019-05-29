/*
** EPITECH PROJECT, 2019
** unalias
** File description:
** unalias
*/

#include "exec.h"

void remove_line(char ****alias, int idx)
{
    free(alias[0][idx]);
    alias[0][idx] = NULL;
    for (int i = idx; alias[0][i + 1] != NULL; i++) {
        alias[0][i] = my_copy_args(alias[0][i], alias[0][i + 1]);
        free(alias[0][i + 1]);
        alias[0][i + 1] = NULL;
    }
}

void re_write_alias2(int i, int *idx, char ***alias, all_t *all)
{
    int index = *idx;

    for (int j = 0; alias[i][j] != NULL; j++) {
        for (int k = 0; alias[i][j][k] != '\0'; k++, index++)
            all->alias[index] = alias[i][j][k];
        all->alias[index] = ' ';
        index++;
    }
    *idx = index;
}

void re_write_alias(char ***alias, all_t *all)
{
    int size = 0;
    int idx = 0;

    for (int i = 0; alias[i] != NULL; i++) {
        for (int j = 0; alias[i][j] != NULL; j++)
            size += (my_strlen(alias[i][j]) + 1);
        size += 1;
    }
    all->alias = malloc(sizeof(char) * (size + 2));
    for (int i = 0; alias[i] != NULL; i++) {
        re_write_alias2(i, &idx, alias, all);
        all->alias[idx] = '\n';
        idx++;
    }
    all->alias[idx] = '\0';
}

void remove_unalias(char *buff, all_t *all, int check)
{
    char ***alias = NULL;

    alias = fill_alias_tab(buff, alias);
    for (int j = 1; all->args[j] != NULL; j++) {
        for (int i = 0; alias[i] != NULL; i++)
            if (my_strcmp(alias[i][0], all->args[j]) == 0) {
                remove_line(&alias, i);
                check = 1;
                break;
            }
    }
    if (check != 0)
        re_write_alias(alias, all);
}

void unalias(all_t *all)
{
    int size = 0;

    for (; all->args[size] != NULL; size++);
    if (size == 1) {
        my_puterror("unalias: Too few arguments.\n");
        all->exit_code = 1;
        return;
    }
    remove_unalias(all->alias, all, 0);
}