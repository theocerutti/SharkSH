/*
** EPITECH PROJECT, 2019
** utils autocompletion
** File description:
** sharkSH
*/

#include "exec.h"

char *update_cline(all_t *all, cmdline_t *cline)
{
    char *new_cline = NULL;
    char *cmd = my_strcpy_auto(cline->line);
    char *add = my_strcpy_auto((char *)all->complete.vector[all->index_comp]);
    int add_index = 0;

    for (int i = 0, w = 0; cmd[i] != '\0'; i++) {
        if ((i == 0 && cmd[i] > 31 && cmd[i] < 127) ||
        (i != 0 && cmd[i - 1] == ' '))
            w += 1;
        add_index = i;
        if (w == all->str_on + 1)
            break;
    }
    if (all->str_on == -1)
        cmd[add_index + 1] = '\0';
    else
        cmd[add_index] = '\0';
    new_cline = my_concat(cmd, add);
    return (new_cline);
}

int my_strncmp(char *ref, char *test, int len)
{
    for (int i = 0; i < len; i++)
        if (ref[i] != test[i])
            return (1);
    return (0);
}

char *my_strcpy_auto(char *to_copy)
{
    char *copy = NULL;
    int len = strlen(to_copy);

    copy = malloc(len + 1);
    for (int i = 0; i < len; i++) {
        copy[i] = to_copy[i];
        copy[i + 1] = '\0';
    }
    return (copy);
}

char *my_concat(char *str1, char *str2)
{
    char *res = NULL;
    int i = 0;

    res = malloc(strlen(str1) + strlen(str2) + 1);
    res[strlen(str1) + strlen(str2)] = '\0';
    for (int w = 0; str1[w] != '\0'; i++, w++)
        res[i] = str1[w];
    for (int w = 0; str2[w] != '\0'; i++, w++)
        res[i] = str2[w];
    return (res);
}