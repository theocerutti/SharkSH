/*
** EPITECH PROJECT, 2019
** complete_quotes
** File description:
** complete_quotes
*/

#include "exec.h"

char *concat_first(char *s1, char *s2, char *str)
{
    int idx = 0;

    str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 2));
    for (int i = 0; s1[i] != '\0'; i++, idx++)
        str[idx] = s1[i];
    str[idx] = ' ';
    idx++;
    for (int i = 0; s2[i] != '\0'; i++, idx++)
        str[idx] = s2[i];
    str[idx] = '\0';
    return (str);
}

char **concat_first_two(char **args)
{
    char **str = NULL;
    int size = 0;

    for (; args[size] != NULL; size++);
    if (size == 0 || size == 1) return (args);
    str = malloc(sizeof(char *) * (size));
    str[0] = concat_first(args[0], args[1], str[0]);
    if (size == 2) {
        str[1] = NULL;
        return (str);
    }
    for (int i = 2, j = 1; args[i] != NULL; i++, j++)
        str[j] = my_strcpy(args[i], str[j]);
    str[size - 1] = NULL;
    return (str);
}

char **args_in_tab(char *str)
{
    int last = 0;
    char **copy = NULL;
    int j = 0;
    char *new = NULL;

    if (my_strlen(str) <= 0) return (NULL);
    new = malloc(sizeof(char) * (my_strlen(str) - 1));
    for (; str[last] != '\0'; last++);
    if_double_quote(str);
    if (my_strcmp(str, "\"\"") == 0 || my_strcmp(str, "\'\'") == 0)
        return (NULL);
    if ((str[0] == '\"' && str[last - 1] == '\"') ||
    (str[0] == '\'' && str[last - 1] == '\'')) {
        for (int i = 1; str[i + 1] != '\0'; i++, j++)
            new[j] = str[i];
        new[j] = '\0';
        copy = str_word_array(new);
        return (concat_first_two(copy));
    }
    return (str_word_array(str));
}

void remove_parenthesis(all_t *all, int idx, int last, int deb)
{
    char *copy = NULL;
    int index = 0;

    for (; all->input[deb] != '\0'; deb++)
        if (all->input[deb] != ' ' && all->input[deb] != '\t'
        && all->input[deb] != '\n')
            break;
    for (; all->input[idx] != '\0'; idx++);
    for (last = idx - 1; last != 0; last--)
        if (all->input[last] != ' ' && all->input[last] != '\t'
        && all->input[last] != '\n' && all->input[last] != '\0')
            break;
    if (last == 0) return;
    if (all->input[deb] != '(' || all->input[last] != ')') return;
    copy = malloc(sizeof(char) * (last - deb + 2));
    for (int i = deb + 1; i != last; i++, index++)
        copy[index] = all->input[i];
    copy[index] = '\0';
    all->input = my_strcpy(copy, all->input);
}

char *manage_back_line(all_t *a, char *str, int k, int size2)
{
    char *input = NULL;

    remove_parenthesis(a, 0, 0, 0);
    for (k = 1; a->input[k] != '\0'; k++)
        if (a->input[k - 1] != '\\' && a->input[k] == '\\' && a->input[k + 1]
        == 'n' && operand_in_quote(a->input, "\\n") == 0) break;
    if (k == 0 || a->input[k] == '\0' || a->input[k + 1] == '\0'
    || a->input[k + 2] == '\0') return (NULL);
    input = malloc(sizeof(char) * (k + 1));
    for (int i = 0; i != k; i++)
        input[i] = a->input[i];
    input[k] = '\0';
    for (int i = k + 2; a->input[i] != '\0'; i++)
        size2++;
    str = malloc(sizeof(char) * (size2 + 1));
    for (int i = k + 2, j = 0; a->input[i] != '\0'; i++, j++)
        str[j] = a->input[i];
    str[size2] = '\0';
    a->input = my_strcpy(input, a->input);
    return (str);
}