/*
** EPITECH PROJECT, 2019
** read_cmdline_utils
** File description:
** read_cmdline_utils
*/

#include "exec.h"

char *insert_char_line(char *line, int index, char c)
{
    int i = 0;

    for (i = my_strlen(line) + 1; i >= index; i--) {
        line[i + 1] = line[i];
    }
    line[i + 1] = c;
    return (line);
}

void delete_index_char(char *line, int index)
{
    for (int i = index; i < my_strlen(line) + 1; i++)
        line[i] = line[i + 1];
}

int putcap(int c)
{
    write(fd_out, &c, 1);
    return (0);
}

void exec_cap(char *cap)
{
    tputs(cap, 1, &putcap);
}