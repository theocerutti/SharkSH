/*
** EPITECH PROJECT, 2019
** usefull2.c
** File description:
** usefull
*/

#include "exec.h"

void my_putchar(char c)
{
    write(fd_out, &c, 1);
}

int my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(nb * -1);
        return (0);
    }
    if (nb < 10) {
        my_putchar(nb + 48);
        return (0);
    }
    my_put_nbr(nb / 10);
    my_putchar((nb % 10) + 48);
    return (0);
}

char *my_strcpy(char *src, char *str)
{
    if (src == NULL)
        return (NULL);
    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    for (int i = 0; src[i] != '\0'; i++)
        str[i] = src[i];
    str[my_strlen(src)] = '\0';
    return (str);
}

int my_strcmp(char *str, char *cmp)
{
    if (cmp == NULL || str == NULL)
        return (1);
    if (my_strlen(str) != my_strlen(cmp) && str[my_strlen(str) - 1] != '\n')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != cmp[i] && i != my_strlen(str) - 1)
            return (1);
    }
    return (0);
}

int my_strcmp_env(char *str, char *cmp)
{
    for (int i = 0; str[i] != '='; i++) {
        if (str[i] != cmp[i])
            return (1);
    }
    return (0);
}