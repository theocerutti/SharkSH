/*
** EPITECH PROJECT, 2019
** usefull
** File description:
** usefull
*/

#include "exec.h"

int my_strlen(char const *str)
{
    int size = 0;

    if (!str)
        return (0);
    for (int i = 0; str[i] != '\0'; i++)
        size++;
    return (size);
}

void my_putstr(char const *str)
{
    int i = 0;

    if (!str)
        return;
    for (; str[i]; i++);
    write(fd_out, str, i);
}

char *int_to_str(int result, int size_result)
{
    int unit = 0;
    int i = size_result - 1;
    char *str = NULL;

    str = malloc(sizeof(char) * size_result + 1);
    while (result >= 10) {
        unit = result % 10;
        str[i] = unit + 48;
        result = result - unit;
        result = result / 10;
        i--;
    }
    str[0] = result + 48;
    str[size_result] = '\0';
    return (str);
}

int my_getnbr(char *str)
{
    int size = my_strlen(str);
    long res = 0;
    int sign = 1;
    int i = 0;
    int size_nbr = 0;

    if (size == 0)
        return (0);
    for (; str[i] == '-' || str[i] == '+'; i++)
        if (str[i] == '-')
            sign *= (-1);
    for (; i < size; i++, size_nbr++) {
        if (str[i] >= '0' && str[i] <= '9') {
            res = res * 10 + (str[i] - 48);
        } else
            break;
    }
    return (res * sign);
}

char *my_strcat_path(char *str, char *next)
{
    char *new = NULL;
    int idx = 0;
    int size = my_strlen(str) + my_strlen(next) + 2;

    if (size == 0)
        return (NULL);
    new = malloc(sizeof(char) * size);
    for (; str[idx] != '\0'; idx++)
        new[idx] = str[idx];
    new[idx] = '/';
    idx++;
    for (int i = 0; next[i] != '\0'; i++) {
        new[idx] = next[i];
        idx++;
    }
    new[idx] = '\0';
    return (new);
}