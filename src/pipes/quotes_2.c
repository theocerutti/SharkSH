/*
** EPITECH PROJECT, 2019
** quotes
** File description:
** quotes
*/

#include "exec.h"

char modif_slash(char *origine, int *j)
{
    j[0] += 1;
    switch (origine[j[0]]) {
        case 'a':
            return (7);
        case 'b':
            return (8);
        case 't':
            return (9);
        case 'n':
            return (10);
        case 'v':
            return (11);
        case 'f':
            return (12);
        case 'r':
            return (13);
    }
    j[0]--;
    return (0);
}

int is_sp(char c)
{
    char *tab_special = "abtnvfr";

    for (int i = 0; tab_special[i] != '\0'; i++)
        if (tab_special[i] == c)
            return (1);
    return (0);
}

void transform_back_line(all_t *all)
{
    char *str = malloc(strlen(all->input) + 1);
    int a = 0;
    int quote = -1;
    int double_quote = -1;

    for (int i = 0; all->input[i] != '\0'; i++) {
        if (all->input[i] == '\'')
            quote *= -1;
        if (all->input[i] == '"')
            double_quote *= -1;
        if (i > 0 && all->input[i] == 'n' && all->input[i - 1] == '\\' && \
        quote == -1 && double_quote == -1) {
            str[a - 1] = ';';
        } else {
            str[a++] = all->input[i];
        }
    }
    str[a] = '\0';
    all->input = str;
}