/*
** EPITECH PROJECT, 2019
** my_pipe
** File description:
** my_pipe
*/

#include "exec.h"

int error_match_special(char *str)
{
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'' && a != 1)
            a = 1;
        else if (str[i] == '\'' && a == 1)
            a = 2;
        if (str[i] == '"' && a != 2)
            a = 2;
        else if (str[i] == '"' && a == 2)
            a = 1;
    }
    if (a == 1) {
        fprintf(stderr, "Unmatched \'\"\'.\n");
        return (84);
    } else if (a == 2) {
        fprintf(stderr, "Unmatched \'\'\'.\n");
        return (84);
    }
    return (0);
}