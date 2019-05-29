/*
** EPITECH PROJECT, 2019
** input_errors
** File description:
** input errors for minishell2
*/

#include "exec.h"

int next_com3(char *str, int i)
{
    while (str[i] != '\0') {
        if (str[i] == ';' || str[i] == '>')
            return (84);
        if (str[i] != ';' && str[i] != '>' && str[i] != ' ')
            return (0);
        i++;
    }
    return (-1);
}

int next_command2(char *str, int i)
{
    while (str[i] != '\0') {
        if (str[i] == '|' || str[i] == '<' || str[i] == '>')
            return (84);
        if (str[i] != '|' && str[i] != '>' && str[i] != '<' &&
        str[i] != ' ')
            return (0);
        i++;
    }
    return (-1);
}

int next_command(char *s, int i, int idx)
{
    int nb = 0;

    if ((s[i] == ';' && (s[i + 1] == '|' ||
    s[i +1 ] == '>' || s[i + 1] == '<')) ||
    (s[i] == '|' && (s[i + 1] == '>' ||
    s[i + 1] == ';')))
        return (84);
    i++;
    idx = i;
    if (s[i - 1] == ';' && (nb = next_command2(s, i) != -1))
        return (nb);
    i = idx;
    if (s[i - 1] == '|' && (nb = next_com3(s, i) != -1))
        return (nb);
    i--;
    if (s[i] == '&' && (s[i + 1] == '&' || (i != 0 && s[i - 1] == '&')))
        return (0);
    return (84);
}

int pipe_error(char *str, int i)
{
    while (str[i] != '\0') {
        if (str[i] == '<')
            return (84);
        if (str[i] != ' ' && str[i] != '<')
            return (0);
        i++;
    }
    return (84);
}

int error_input(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (((str[i] == '|' && str[i + 1] != '|') ||
        str[i] == '&') && next_command(str, i, 0) == 84) {
            my_puterror("Invalid null command.\n");
            return (84);
        }
        if (str[i] == '|' && pipe_error(str, i+ 1) == 84) {
            my_puterror("Ambiguous input redirect.\n");
            return (84);
        }
    }
    if (error_input2(str, 0) == 84) {
        my_puterror("Missing name for redirect.\n");
        return (84);
    }
    return (0);
}