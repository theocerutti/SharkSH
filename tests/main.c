/*
** EPITECH PROJECT, 2019
** tests
** File description:
** tests
*/

#include "unit_tests/include/unity.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>

void init_all(all_t *all, int len2, char **env);
void add_globings(arraylist_t *list, char *str);

void test_globings(void)
{
    char *txt = "[A-z]n?*y";
    char **args = malloc(sizeof(char *) * 2);
    char *txtmalloc = malloc(sizeof(char) * (strlen(txt) + 1));
    char **list = NULL;

    strcpy(txtmalloc, txt);
    args[0] = txtmalloc;
    args[1] = 0;
    list = process_globings(args);
    ut_assert_str_eq(list[0], "unity");
}

void test_add_globings(void)
{
    arraylist_t *list = new_arraylist(1);
    char *txt = "[A-z]n?*y";
    char *txtmalloc = malloc(sizeof(char) * (strlen(txt) + 1));

    strcpy(txtmalloc, txt);
    add_globings(list, txtmalloc);
    ut_assert(list->size == 1);
    ut_assert_str_eq(list->list[0], "unity");
}

int main(void)
{
    register(test_history, "History - test 1");
    register(test_get_comp, "Verify get_comp");
    register(test_get_bin, "Verify get_bin");
    register(test_globings, "Verify globings");
    register(test_add_globings, "Verify add_globings");
    exec_test();
    system("lua ./tests/unity-update.lua");
    return (0);
}