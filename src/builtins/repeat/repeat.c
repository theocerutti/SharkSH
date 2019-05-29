/*
** EPITECH PROJECT, 2019
** repeat
** File description:
** repeat
*/

#include "exec.h"

static int check_error_repeat(char **tab_cmd)
{
    int args = 0;

    for (args = 0; tab_cmd[args] != NULL; args++);
    if (args < 3) {
        fprintf(stderr, "repeat: Too few arguments.\n");
        return (ERROR);
    }
    if (!my_str_isnum_neg(tab_cmd[1])) {
        fprintf(stderr, "repeat: Badly formed number.\n");
        return (ERROR);
    }
    return (SUCCESS);
}

static char **get_command_tab(all_t *all)
{
    char *s = NULL;
    int size = 0;
    int len = 0;

    for (int i = 2; all->args[i] != NULL; i++)
        size += strlen(all->args[i]) + 2;
    s = malloc(sizeof(char) * size);
    strcpy(s, all->args[2]);
    for (int i = 3; all->args[i] != NULL; i++) {
        len = strlen(s);
        s[len] = ' ';
        s[len + 1] = '\0';
        strcat(s, all->args[i]);
    }
    s[strlen(s)] = '\0';
    all->input = s;
    return (str_word_array(s));
}

static char **cpy_tab(char **arg)
{
    char **new_tab;
    int size;

    for (size = 0; arg[size] != NULL; size++);
    new_tab = malloc(sizeof(char *) * (size + 1));
    new_tab[size] = NULL;
    for (int i = 0; arg[i] != NULL; i++) {
        new_tab[i] = malloc(strlen(arg[i]) + 1);
        new_tab[i][strlen(arg[i])] = '\0';
        for (int j = 0; arg[i][j] != '\0'; j++)
            new_tab[i][j] = arg[i][j];
    }
    return (new_tab);
}

void repeat(all_t *all)
{
    int nb_repeat = 0;
    char **arg = cpy_tab(all->args);

    if (check_error_repeat(all->args) == ERROR) {
        all->exit_code = 1;
        return;
    }
    nb_repeat = atoi(all->args[1]);
    for (int i = 0; i < nb_repeat; i++) {
        all->args = get_command_tab(all);
        exec_command(all);
        all->args = arg;
    }
}