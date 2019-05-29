/*
** EPITECH PROJECT, 2019
** echo
** File description:
** echo
*/

#include "exec.h"

int get_size_var(char *arg, int i)
{
    int size = 0;

    for (; arg[i] == '$'; i += 1);
    for (size = 0; !is_in(arg[i], " $\'\"") && arg[i] != '\0'; size++, i++)
        if (arg[i] != '$')
            size++;
    return (size);
}

static int get_size_param_echo(char **args)
{
    return (strlen(my_tab_to_str(args, " ")));
}

char *get_param_echo(char **args, int have_n_arg)
{
    char *arg = malloc(sizeof(char) * get_size_param_echo(args));
    int index = 2;

    if (args[1] == NULL)
        return (NULL);
    if (have_n_arg)
        index++;
    if (args[index - 1] == NULL)
        return (NULL);
    strcpy(arg, args[index - 1]);
    for (int i = index; args[i] != NULL; i++) {
        strcat(arg, " ");
        strcat(arg, args[i]);
    }
    return (arg);
}