/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** my_realloc src file Antoine Maillard
*/

#include "exec.h"

char *concat_space(char *str1, char *str2)
{
    int len1;
    int len2;
    char *new;
    int w = 0;

    for (len1 = 0; str1[len1] != '\0'; len1++);
    for (len2 = 0; str2[len2] != '\0'; len2++);
    if (str1[len1 - 1] == ' ')
        len1 -= 1;
    new = malloc(len1 + len2 + 2);
    for (int i = 0; i < len1; i++, w++) {
        new[w] = str1[i];
        new[w + 1] = ' ';
    }
    w += 1;
    for (int i = 0; i < len2; i++, w++) {
        new[w] = str2[i];
        new[w + 1] = '\0';
    }
    return (new);
}

void my_realloc(char **env)
{
    int len;
    char **new;

    for (len = 0; env[len] != NULL; len++);
    new = malloc(sizeof(char *) * len + 1);
    for (int i = 0; i <= len; i++)
        new[i] = env[i];
    env = malloc(sizeof(char *) * len + 2);
    for (int i = 0; i <= len; i++)
        env[i] = new[i];
}

void fill_new(char *new, char *env, char *str)
{
    int i;

    for (i = 0; env[i] != '\0'; i++)
        new[i] = env[i];
    for (int w = 0, z = 0; str[w] != '\0'; w++) {
        if (z == 1 && str[w] != '\'') {
            new[i] = str[w];
            i += 1;
        }
        if (str[w] == '\'')
            z = 1;
    }
}

char *concat_env_add(char *env, char *str)
{
    char *new;
    int len;

    for (len = 0; env[len] != '\0'; len++);
    for (int i = 0, z = 0; str[i] != '\0'; i++) {
        if (z == 1)
            len += 1;
        if (str[i] == '\'')
            z = 1;
    }
    len -= 1;
    new = malloc(len + 1);
    new[len] = '\0';
    fill_new(new, env, str);
    return (new);
}