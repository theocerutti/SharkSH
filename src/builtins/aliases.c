/*
** EPITECH PROJECT, 2019
** aliases
** File description:
** aliases
*/

#include "exec.h"

int save_alias2(all_t *all)
{
    prepare_alias(all->input);
    all->args = str_word_array(all->input);
    if (all->args[1] == NULL) {
        my_putstr(all->alias);
        return (1);
    }
    quotes(all);
    if (my_strcmp_cd(all->args[1], "alias") == 1) {
        my_puterror("alias: Too dangerous to alias that.\n");
        all->exit_code = 1;
        return (1);
    }
    return (0);
}

char **check_args(char **args, int size, int space, char **copy)
{
    char **first = NULL;

    for (int i = 0; args[0][i] != '\0'; i++)
        if (args[0][i] == ' ')
            space++;
    if (space == 0)
        return (args);
    copy = my_copy_args(copy, args);
    for (; args[size] != NULL; size++);
    free(args);
    args = malloc(sizeof(char *) * (size + 2 + space));
    first = str_word_array(copy[0]);
    space = 0;
    for (int i = 0; first[i] != NULL; i++, space++)
        args[space] = my_strcpy(first[i], args[space]);
    for (int i = 1; copy[i] != NULL; i++, space++)
        args[space] = my_strcpy(copy[i], args[space]);
    args[space] = NULL;
    return (args);
}

int alias_loop(char ***alias, all_t *all, int i, int *loop)
{
    if (*loop == 4) {
        *loop = 0;
        return (1);
    }
    for (int j = 0; alias[j] != NULL; j++) {
        if (my_strcmp_cd(alias[i][0], alias[j][1]) == 1) {
            my_puterror("Alias loop.\n");
            init(all, NULL, 0);
        }
    }
    return (0);
}

int manage_alias2(char ***alias, char **args, int loop, all_t *all)
{
    if (my_strcmp_cd(alias[all->exit_code][0], args[0]) == 1) {
        if (alias_loop(alias, all, all->exit_code, &loop) == 1)
            return (84);
        loop++;
        free(args[0]);
        args[0] = my_strcpy(alias[all->exit_code][1], 0);
        args = check_args(args, 0, 0, NULL);
        args = manage_alias(args, all);
    }
    return (0);
}

char **manage_alias(char **args, all_t *all)
{
    char ***alias = NULL;
    static int loop = 0;
    int tmp = all->exit_code;

    if (my_strcmp_cd("alias", args[0]) == 1) return (args);
    alias = fill_alias_tab(all->alias, alias);
    for (int i = 0; alias[i] != NULL; i++) {
        all->exit_code = i;
        if (manage_alias2(alias, args, loop, all) == 84)
            return (args);
    }
    all->exit_code = tmp;
    free(alias);
    return (args);
}