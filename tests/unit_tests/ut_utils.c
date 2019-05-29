/*
** EPITECH PROJECT, 2018
** ut_utils
** File description:
** ut_utils
*/

#include <unistd.h>
#include <stdio.h>
#include "./include/unittest.h"

void mwrite(char const *str)
{
    int index = 0;

    while (str[index++]);
    write(1, str, index);
}

void mwrite_int(int a)
{
    char str[12];

    sprintf(str, "%d", a);
    mwrite(str);
}

void comp_err(char *a, char *b)
{
    mwrite("[\x1B[34m----\x1B[0m] ");
    mwrite(running->name);
    mwrite(": Assertion failed: The expression (");
    mwrite(a);
    mwrite(") == (");
    mwrite(b);
    mwrite(") is false\n");
    mwrite("[\x1B[31mFAIL\x1B[0m] ");
    mwrite(running->name);
    mwrite("::");
    mwrite(running->desc);
    mwrite("\n");
}
