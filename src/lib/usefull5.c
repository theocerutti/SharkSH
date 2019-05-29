/*
** EPITECH PROJECT, 2019
** usefull
** File description:
** usefull
*/

#include "exec.h"

char *my_itoa(int nb)
{
    char *new_str = malloc(sizeof(char) * 15);
    int nb_digit = 0;
    float multi = 0.1;
    int i = 0;
    int plus = 0;

    if (nb < 0) {
        new_str[0] = '-';
        plus = 1;
        nb *= -1;
    }
    for (long nb_s = nb; nb_s > 0; nb_s /= 10, multi *= 10)
        nb_digit += 1;
    nb_digit = (nb == 0) ? 1 : nb_digit;
    multi = (nb == 0) ? 10 : multi;
    for (i = plus; i != nb_digit + plus; i++, multi /= 10)
        new_str[i] = (nb / (int)multi % 10) + '0';
    new_str[i] = '\0';
    return (new_str);
}

void my_puterror(char *str)
{
    char c = 0;

    if (str == NULL)
        return;
    for (int i = 0; str[i] != '\0'; i++) {
        c = str[i];
        write(2, &c, 1);
    }
}

char *get_alias(int *idx, char *str, char *alias, int check)
{
    int size = 0;

    for (int i = *idx; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == '\n') {
            size = i;
            break;
        }
    }
    alias = malloc(sizeof(char) * (size + 1));
    for (int i = *idx, j = 0; str[i] != '\0'; i++, j++) {
        if (((str[i] == ' ' && check == 0) ||
        (str[i] == '\n' && check == 1))) {
            *idx = i + 1;
            alias[j] = '\0';
            return (alias);
        }
        alias[j] = str[i];
    }
    return (NULL);
}

char ***fill_alias_tab(char *str, char ***alias)
{
    int size = 0;
    int idx = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == '\n')
            size++;
    alias = malloc(sizeof(char **) * (size + 1));
    for (int i = 0, check = 0; i < size; i++) {
        alias[i] = malloc(sizeof(char *) * 3);
        alias[i][0] = get_alias(&idx, str, alias[i][0], check);
        check = 1;
        alias[i][1] = get_alias(&idx, str, alias[i][1], check);
        check = 0;
        alias[i][2] = NULL;
    }
    alias[size] = NULL;
    return (alias);
}