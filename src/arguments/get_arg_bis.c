/*
** EPITECH PROJECT, 2019
** get_arguments
** File description:
** get_arguments
*/

#include "exec.h"

char **get_comp(char *bin, char **args)
{
    char **comp = NULL;
    int size = 0;
    int idx = 1;

    for (; args[size] != NULL; size++);
    comp = malloc(sizeof(char *) * (size + 2));
    comp[0] = my_strcpy(bin, comp[0]);
    for (int i = 0; args[i] != NULL; i++) {
        comp[idx] = my_strcpy(args[i], comp[idx]);
        idx++;
    }
    comp[size + 1] = NULL;
    return (comp);
}

char *get_bin(char *str, int *ch)
{
    int size = 0;
    char *bin = NULL;

    for (; str[size] != '\0' && str[size] != ' '; size++);
    bin = malloc(sizeof(char) * (size + 1));
    for (int i = 0; str[i] != '\0' && str[i] != ' '; i++)
        bin[i] = str[i];
    bin[size] = '\0';
    if (str[size] == '\0')
        *ch = 0;
    for (int i = size; str[i] != '\0'; i++)
        if (str[i] != ' ')
            *ch = size;
    return (bin);
}

char *get_arg_list(char *str, int idx, char *dest)
{
    int size = 0;
    int i = 0;

    for (; str[size] != '\0'; size++);
    dest = malloc(sizeof(char) * (size + 1));
    for (; str[idx] != ' ' && str[i] != '\0'; idx++) {
        dest[i] = str[idx];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char **get_args_list(char *str, int *ch, int *nb, int index)
{
    int idx = *ch;
    char **args = NULL;

    if (*ch == 0) {
        args = malloc(sizeof(char *) * 1);
        args[0] = NULL;
        return (args);
    }
    for (int i = *ch; str[i] != '\0'; i++)
        if (str[i] == ' ')
            *nb = *nb + 1;
    args = malloc(sizeof(char *) * (*nb + 1));
    for (; str[idx] != '\0'; idx++)
        if (str[idx] == ' ') {
            args[index] = get_arg_list(str, idx + 1, args[index]);
            index++;
        }
    args[*nb] = NULL;
    *ch = 0;
    return (args);
}