/*
** EPITECH PROJECT, 2019
** add cmd to history
** File description:
** Shark SH
*/

#include "exec.h"

void reduce(char *cmd, int i)
{
    for (int w = i + 1; cmd[w] != '\0'; w++)
        cmd[w] = cmd[w + 1];
}