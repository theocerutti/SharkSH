/*
** EPITECH PROJECT, 2019
** echo
** File description:
** echo
*/

#include "exec.h"

static void print_backslash2(char c)
{
    switch (c) {
        case 'n':
            my_putchar('\n');
            break;
        case 'v':
            my_putchar('\v');
            break;
        case 'f':
            my_putchar('\f');
            break;
        case '\'':
            my_putstr("\\\'");
            break;
        case '\"':
            my_putstr("\\\"");
            break;
        default:
            my_putchar(c);
    }
}

void switch_backslash(char *arg, int *i)
{
    switch (arg[*i]) {
        case 'a':
            my_putchar('\a');
            break;
        case 'b':
            my_putchar('\b');
            break;
        case 't':
            my_putchar('\t');
            break;
        case 'r':
            my_putchar('\r');
            break;
        default:
            print_backslash2(arg[*i]);
    }
}

void print_backslash(char *arg, int *i, int quoted)
{
    if (quoted == NO_QUOTE) {
        *i += 1;
        if (arg[*i] == '\'' || arg[*i] == '\"')
            my_putchar(arg[*i]);
    } else {
        *i += 1;
        switch_backslash(arg, i);
        *i += 1;
    }
}