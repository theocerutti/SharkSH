/*
** EPITECH PROJECT, 2019
** exit_prog
** File description:
** change dir
*/

#include "exec.h"

char *my_tab_to_str(char **to_copy, char *separator)
{
    int index_str = 0;
    char *str = NULL;

    if (to_copy == NULL)
        return (str);
    for (int i = 0; to_copy[i] != NULL; i++) {
        for (int j = 0; to_copy[i][j] != '\0'; j++, index_str++);
        for (int h = 0; separator[h] != '\0'; h++, index_str++);
    }
    str = malloc(sizeof(char) * (index_str + 1));
    index_str = 0;
    for (int i = 0; to_copy[i] != NULL; i++) {
        for (int j = 0; to_copy[i][j] != '\0'; j++, index_str++) {
            str[index_str] = to_copy[i][j];
        }
        for (int h = 0; separator[h] != '\0'; h++, index_str++)
            str[index_str] = separator[h];
    }
    str[index_str - 1] = '\0';
    return (str);
}

char **my_strcpy_tab(char **dest, char **src)
{
    int i = 0;

    for (i = 0; src[i] != NULL; i++) {
        dest[i] = my_strcpy(dest[i], src[i]);
    }
    dest[i] = NULL;
    return (dest);
}

void my_exit(all_t *all)
{
    if (all->args[1] == NULL)
        exit(0);
    if (all->args[1][0] > '9' || all->args[1][0] < '0') {
        my_puterror("exit: Expression Syntax.\n");
        all->exit_code = 1;
        return;
    } else
        exit(my_getnbr(all->args[1]));
    return;
}