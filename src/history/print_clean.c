/*
** EPITECH PROJECT, 2019
** print clearly the cmd
** File description:
** sharksh
*/

#include "exec.h"

char *add_special_space_print(char *cmd)
{
    int len_new = strlen(cmd);
    char *final_cmd = NULL;

    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] == '(' || cmd[i] == ')' || cmd[i] == '|' || cmd[i] == ';' ||
        cmd[i] == '[' || cmd[i] == ']' || cmd[i] == '&')
            len_new += 2;
    final_cmd = malloc(len_new + 1);
    for (int i = 0; i <= len_new; i++)
        final_cmd[i] = '\0';
    for (int i = 0, w = 0; cmd[i] != '\0'; i++, w++)
        finalize_cmd(&i, &w, final_cmd, cmd);
    return (final_cmd);
}

void print_command_clean(char *cmd)
{
    reduce_space(cmd);
    cmd = add_special_space_print(cmd);
    my_putstr(cmd);
    my_putstr("\n");
}