/*
** EPITECH PROJECT, 2019
** str_word_array.c
** File description:
** src file Antoine Maillard
*/

#include <stdlib.h>

int count_word(char *);

char *concat_file(char *str1, char *str2)
{
    int len1;
    int len2;
    char *new;
    int w = 0;

    for (len1 = 0; str1[len1] != '\0'; len1++);
    for (len2 = 0; str2[len2] != '\0'; len2++);
    if (str1[len1 - 1] == '/')
        len1 -= 1;
    new = malloc(len1 + len2 + 2);
    for (int i = 0; i < len1; i++, w++) {
        new[w] = str1[i];
        new[w + 1] = '/';
    }
    w += 1;
    for (int i = 0; i < len2; i++, w++) {
        new[w] = str2[i];
        new[w + 1] = '\0';
    }
    return (new);
}

char *concat_env(char *str1, char *str2)
{
    int len1;
    int len2;
    char *new;
    int w = 0;

    for (len1 = 0; str1[len1] != '\0'; len1++);
    for (len2 = 0; str2[len2] != '\0'; len2++);
    if (str1[len1 - 1] == '=')
        len1 -= 1;
    new = malloc(len1 + len2 + 2);
    for (int i = 0; i < len1; i++, w++) {
        new[w] = str1[i];
        new[w + 1] = '=';
    }
    w += 1;
    for (int i = 0; i < len2; i++, w++) {
        new[w] = str2[i];
        new[w + 1] = '\0';
    }
    return (new);
}

void fill_word(char **str_ar, char *str, int *dt, int ind)
{
    for (int i = ind - dt[0], w = 0; i <= ind; i++) {
        if (i >= 0 && str[i] > 32 && str[i] < 127) {
            str_ar[dt[2]][w] = str[i];
            str_ar[dt[2]][w + 1] = '\0';
            w++;
        }
    }
    str_ar[count_word(str)] = NULL;
}

int count_word(char *str)
{
    int count = 0;

    for (int i = 0, z = 0; str[i] != '\0'; i++) {
        if (str[i] <= 32 || str[i] >= 127)
            z = 0;
        if (str[i] > 32 && str[i] < 127 && z == 0) {
            count++;
            z = 1;
        }
    }
    return (count);
}

char **str_word_array(char *str)
{
    char **str_ar = malloc(sizeof(char *) * (count_word(str) + 1));
    int dt[4] = {0, count_word(str), 0, 0};

    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] <= 32 || str[i] >= 127) && dt[3] == 1) {
            dt[3] = 0;
            str_ar[dt[2]] = malloc(dt[0] + 1);
            fill_word(str_ar, str, dt, i);
            dt[0] = 0;
            dt[2] += 1;
        } else if (str[i] > 32 && str[i] < 127 && dt[3] == 0)
            dt[3] = 1;
        if (dt[3] == 1)
            dt[0] += 1;
        if (str[i + 1] == '\0' && dt[3] == 1) {
            str_ar[dt[2]] = malloc(dt[0] + 1);
            fill_word(str_ar, str, dt, i);
        }
    }
    return (str_ar);
}
