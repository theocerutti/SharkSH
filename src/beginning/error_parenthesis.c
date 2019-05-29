/*
** EPITECH PROJECT, 2019
** error_parenthesis
** File description:
** error_parenthesis
*/

#include "exec.h"

void if_double_quote(char *str)
{
    if (my_strcmp(str, "\"\"") == 0 || my_strcmp(str, "\'\'") == 0)
        my_puterror(": Command not found.\n");
}

char last_char(char *str, int i)
{
    if (i == 0)
        return ('\0');
    for (i = i - 1; i >= 0; i--) {
        if (str[i] != ' ')
            return (str[i]);
    }
    return ('\0');
}

char next_char(char *str)
{
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] != ' ')
            return (str[i]);
    }
    return ('\0');
}

int error_parenthesis(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '|' && (next_char(str + i) == ')' || \
        last_char(str, i) == '(')) {
            fprintf(stderr, "Invalid null command.\n");
            return (84);
        }
        if (str[i] == '<' && str[i + 1] == '<' && last_char(str, i) == '(') {
            fprintf(stderr, "Can't << within ()'s.\n");
            return (84);
        }
        if ((str[i] == '>' || str[i] == '<') && next_char(str + i) == ')') {
            fprintf(stderr, "Missing name for redirect.\n");
            return (84);
        } else if ((str[i] == '>' || str[i] == '<' || str[i] == ';') && \
        last_char(str, i) == '(') {
            fprintf(stderr, "Invalid null command.\n");
            return (84);
        }
    }
    return (0);
}