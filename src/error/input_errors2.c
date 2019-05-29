/*
** EPITECH PROJECT, 2019
** input_errors2
** File description:
** input errors for minishell2
*/

#include "exec.h"

int next_to_redirection(char *str, int idx)
{
    if (str[idx] != '\0' && str[idx] != ' ' && str[idx] != '>' &&
    str[idx] != '<' && str[idx] != '|' && str[idx] != ';')
        return (0);
    while (str[idx] != '\0') {
        if (str[idx] == '|' || str[idx] == ';' ||
        str[idx] == '>' || str[idx] == '<')
            return (84);
        if (str[idx] != ' ' && str[idx] != '|' && str[idx] != ';' &&
        str[idx] != '>' && str[idx] != '<')
            return (0);
        idx++;
    }
    return (84);
}

int error_input2(char *str, int nb)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '>' && str[i + 1] == '>')
            nb = next_to_redirection(str, i + 2);
        if (nb == 84)
            return (nb);
        if (str[i] == '>' && str[i + 1] != '>')
            nb = next_to_redirection(str, i + 1);
        if (nb == 84)
            return (nb);
        if (str[i] == '<' && str[i + 1] == '<')
            nb = next_to_redirection(str, i + 2);
        if (nb == 84)
            return (nb);
        if (str[i] == '<' && str[i + 1] != '<')
            nb = next_to_redirection(str, i + 1);
        if (nb == 84)
            return (nb);
    }
    return (0);
}