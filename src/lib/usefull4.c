/*
** EPITECH PROJECT, 2019
** usefull
** File description:
** usefull
*/

#include "exec.h"

char *my_strcat(char const *dest, char const *src)
{
    int i = 0;
    char *new = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 1));

    for (i = 0; dest[i] != '\0'; i++)
        new[i] = dest[i];
    for (int j = 0; src[j] != '\0'; j++, i++)
        new[i] = src[j];
    new[i] = '\0';
    return (new);
}

int my_str_isnum(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}

int my_str_isalphanum(char const *str)
{
    char s;

    for (int i = 0; str[i] != '\0'; i++) {
        s = str[i];
        if ((s < '0' || s > '9') && ((s < 'A' || s > 'Z') &&
        (s < 'a' || s > 'z')) && s != '_') {
            return (0);
        }
    }
    return (1);
}

int my_str_isalpha(char const *str)
{
    int i = 0;
    int count_same = 0;
    int len = 0;
    char s;

    for (i = 0; str[i] != '\0'; i++) {
        len += 1;
        s = str[i];
        if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z'))
            count_same += 1;
    }
    if (count_same == len || len == 0)
        return (1);
    else
        return (0);
}

int my_str_isnum_neg(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[0] != '-')
            return (0);
    }
    return (1);
}