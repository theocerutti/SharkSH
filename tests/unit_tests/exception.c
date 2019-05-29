/*
** EPITECH PROJECT, 2018
** exception
** File description:
** exception
*/

#include <signal.h>
#include <stdio.h>
#include "./include/unittest.h"
#include "./include/ut_utils.h"

void segfault(int id)
{
    mwrite("Segfault in '");
    mwrite(running->name);
    mwrite("' function\n");
    crash++;
    signal(id, &segfault);
}

void illeg_instruction(int id)
{
    mwrite("Illegal Instruction in '");
    mwrite(running->name);
    mwrite("' function\n");
    crash++;
    signal(id, &illeg_instruction);
}

void buserror(int id)
{
    mwrite("Bus Error in '");
    mwrite(running->name);
    mwrite("' function\n");
    crash++;
    signal(id, &buserror);
}

void arithmerror(int id)
{
    mwrite("Arithmetic Error in '");
    mwrite(running->name);
    mwrite("' function\n");
    crash++;
    signal(id, &arithmerror);
}
