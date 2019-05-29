/*
** EPITECH PROJECT, 2019
** alias utils
** File description:
** sharkSH utils
*/

#include "exec.h"

char *ins_char(char *line, int index, char c)
{
    int i = 0;
    char *new = malloc(strlen(line) + 2);

    for (int i = 0; i <= (int)strlen(line); i++)
        new[i] = line[i];
    for (i = my_strlen(line) + 1; i >= index; i--)
        line[i + 1] = line[i];
    line[i + 1] = c;
    return (line);
}

void prepare_alias(char *cline)
{
    for (int i = 0; cline[i] != '\0'; i++)
        if (cline[i] == 39 || cline[i] == 34)
            delete_index_char(cline, i);
    for (int i = 0, w = 0, doit = 0; cline[i] != '\0'; i++) {
        if ((i == 0 && cline[i] > 31 && cline[i] < 127) ||
        (i != 0 && (cline[i - 1] == ' ' || cline[i - 1] == '\n' ||
        cline[i - 1] == '\t')))
            w += 1;
        if (w == 3 && doit == 0) {
            cline = ins_char(cline, i, 34);
            break;
        }
    }
    cline = ins_char(cline, strlen(cline), 34);
}

void save_alias(all_t *all)
{
    char *copy = NULL;
    int size = 0;
    int idx = 0;

    if (save_alias2(all) == 1) return;
    for (int i = 1; all->args[i] != NULL && i <= 2; i++)
        size += my_strlen(all->args[i]);
    copy = malloc(sizeof(char) * (my_strlen(all->alias) + size + 4));
    for (int i = 0; all->alias[i] != '\0'; i++, idx++)
        copy[idx] = all->alias[i];
    for (int i = 0; all->args[1][i] != '\0'; i++, idx++)
        copy[idx] = all->args[1][i];
    copy[idx] = ' ';
    idx++;
    for (int i = 0; all->args[2][i] != '\0'; i++, idx++)
        copy[idx] = all->args[2][i];
    copy[idx] = '\n';
    idx++;
    copy[idx] = '\0';
    all->alias = my_strcpy(copy, all->alias);
}