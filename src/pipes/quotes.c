/*
** EPITECH PROJECT, 2019
** quotes
** File description:
** quotes
*/

#include "exec.h"

void concat_quotes(all_t *all, int select_1, int select_2)
{
    int k = 0;

    for (int i = select_1 + 1; i <= select_2; i++) {
        all->args[select_1] = my_strcat(all->args[select_1], " ");
        all->args[select_1] = my_strcat(all->args[select_1], all->args[i]);
    }
    for (int i = select_2 + 1; all->args[i] != NULL; i++) {
        all->args[select_1 + 1 + k] = all->args[i];
        k += 1;
    }
    all->args[select_1 + 1 + k] = NULL;
    all->args[select_1]++;
    all->args[select_1][strlen(all->args[select_1]) - 1] = '\0';
}

void delete_quote(all_t *all)
{
    char *str;
    int k = 0;

    for (int i = 0; all->args[i] != NULL; i++) {
        k = 0;
        str = malloc(sizeof(char) * (strlen(all->args[i])) + 1);
        for (int j = 0; all->args[i][j] != '\0'; j++) {
            if (all->args[i][j] == '\\' && is_sp(all->args[i][j + 1])) {
                str[k++] = modif_slash(all->args[i], &j);
                j++;
            } else if (all->args[i][j] == '\\') {
                j++;
            }
            str[k++] = all->args[i][j];
        }
        str[k] = '\0';
        all->args[i] = str;
    }
}

int is_inhib(int j, char c, char *all)
{
    if ((j == 0 || all[j - 1] != '\\') && all[j] == c) {
        return (1);
    } else if ((j < 2 || (all[j - 2] == '\\' && \
    all[j - 1] == '\\')) && all[j] == c)
        return (1);
    return (0);
}

void simple_quotes(all_t *all)
{
    for (int i = 0, select_1 = -1, select_2 = -1; all->args[i] != NULL; i++) {
        for (int j = 0; all->args[i][j] != '\0'; j++) {
            if (is_inhib(j, '\'', all->args[i]) && select_1 == -1) {
                select_1 = i;
            } else if (is_inhib(j, '\'', all->args[i])) {
                select_2 = i;
                concat_quotes(all, select_1, select_2);
                select_1 = -1;
                select_2 = -1;
                j = 0;
                i = 0;
            }
            if (select_1 == select_2)
                select_1 = -1;
        }
    }
    delete_quote(all);
}

void quotes(all_t *all)
{
    for (int i = 0, select_1 = -1, select_2 = -1; all->args[i] != NULL; i++) {
        for (int j = 0; all->args[i][j] != '\0'; j++) {
            if (is_inhib(j, '"', all->args[i]) && select_1 == -1) {
                select_1 = i;
            } else if (is_inhib(j, '"', all->args[i])) {
                select_2 = i;
                concat_quotes(all, select_1, select_2);
                select_1 = -1;
                select_2 = -1;
                j = 0;
                i = 0;
            }
            if (select_1 == select_2)
                select_1 = -1;
        }
    }
    simple_quotes(all);
}