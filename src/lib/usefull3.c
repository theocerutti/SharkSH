/*
** EPITECH PROJECT, 2019
** usefull3
** File description:
** usefull3
*/

#include "exec.h"

char **my_double_strcpy(char **str, char **dest)
{
    int size = 0;
    int idx = 0;

    free(dest);
    for (int i = 0; str[i] != NULL; i++)
        size++;
    dest = malloc(sizeof(char *) * (size + 1));
    for (int i = 0; str[i] != NULL; i++) {
        dest[idx] = my_strcpy(str[i], dest[idx]);
        idx++;
    }
    dest[idx] = NULL;
    return (dest);
}

void print_tab(char **tabb)
{
    for (int i = 0; tabb[i] != NULL; i++) {
        printf("%s\n", tabb[i]);
    }
}

char is_in(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (c);
    }
    return (0);
}

void free_tab(char **tabb)
{
    for (int i = 0; tabb[i] != NULL; i++)
        free(tabb[i]);
    free(tabb);
}

char *big_strcat(int nb_args, ...)
{
    char *ret = "";
    char *str = NULL;

    va_list args;
    va_start(args, nb_args);
    for (int i = 0; i < nb_args; i++) {
        str = va_arg(args, char *);
        ret = my_strcat(ret, str);
    }
    va_end(args);
    return (ret);
}