/*
** EPITECH PROJECT, 2019
** where/which utils
** File description:
** where/which utils
*/

#include "exec.h"

int is_a_shell_builtin(char *cmd, int is_where)
{
    for (int j = 0; builtins[j].name != NULL; j++) {
        if (!strncmp(cmd, builtins[j].name, strlen(builtins[j].name))) {
            if (is_where)
                printf("%s is a shell built-in\n", cmd);
            else
                printf("%s: shell built-in command.\n", cmd);
            return (TRUE);
        }
    }
    return (FALSE);
}

static char *get_name_alias(char *alias)
{
    while (alias[0] != ' ' && alias[0] != '\0')
        alias++;
    return (++alias);
}

int is_an_alias(char *arg, int is_where, char **aliases)
{
    char *aliased = NULL;
    char **alias = NULL;

    for (int i = 0; aliases[i] != NULL; i++) {
        aliased = get_name_alias(aliases[i]);
        alias = str_word_array(aliases[i]);
        if (!strncmp(arg, alias[0], strlen(alias[0]))) {
            if (is_where)
                printf("%s is aliased to %s\n", arg, aliased);
            else
                printf("%s:\taliased to %s\n", arg, aliased);
            return (1);
        }
    }
    return (0);
}
