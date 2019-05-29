/*
** EPITECH PROJECT, 2018
** my_str_to_word_array.c
** File description:
** lib
*/

#include <stdlib.h>

static int is_num_alpha(char s)
{
    if (s == '\n')
        return (1);
    else
        return (0);
}

static void word_add(char const *str, char **tab, int num_word, int modify)
{
    int i = 0;
    int count = 0;
    char s;
    int a = 0;
    int k = 0;

    for (i = 0; str[i] != '\0'; i++) {
        s = str[i];
        if (is_num_alpha(s) == 1 && a == 0) {
            count++;
            a = 1;
        } else if (is_num_alpha(s) == 0 && a == 1)
            a = 0;
        if (a == 0 && count == num_word + modify) {
            tab[num_word][k] = str[i];
            k++;
        }
    }
    tab[num_word][k] = '\0';
}

static void lenght_word(char const *str, char **tab, int num_word)
{
    int i = 0;
    int count = 0;
    char s;
    int lenght_word = 0;
    int a = 0;

    for (i = 0; str[i] != '\0'; i++) {
        s = str[i];
        if (is_num_alpha(s) == 0 && a == 0) {
            count++;
            a = 1;
        } else if (is_num_alpha(s) == 1 && a == 1)
            a = 0;
        if (a == 1 && count == num_word + 1)
            lenght_word++;
    }
    tab[num_word] = malloc(sizeof(char) * (lenght_word + 1));
}

static int count_word(char const *str)
{
    char s;
    int a = 0;
    int count = 0;
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        s = str[i];
        if (is_num_alpha(s) == 0 && a == 0) {
            count++;
            a = 1;
        }
        else if (is_num_alpha(s) == 1 && a == 1)
            a = 0;
    }
    if (i == 0)
        return (0);
    count++;
    return (count);
}

char **word_array_alias(char const *str)
{
    char **tab;
    int i = 0;
    int count = 0;
    int a = 0;

    if (is_num_alpha(str[0]))
        a = 1;
    count = count_word(str);
    tab = malloc(sizeof(char *) * (count + 1));
    for (i = 0; i != count; i++)
        lenght_word(str, tab, i);
    for (i = 0; i != count; i++)
        word_add(str, tab, i, a);
    tab[count - 1] = NULL;
    return (tab);
}
