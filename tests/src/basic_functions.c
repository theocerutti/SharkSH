/*
** EPITECH PROJECT, 2019
** basic functions
** File description:
** sharkSH test
*/

#include "exec.h"

void test_history(void)
{
    char command2[] = "ui";
    all_t all = {NULL, 0, 0, "ls", NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL,
    NULL, vector_create(15), {0}, 0, 0, 0, 0, 0, 0, 0, NULL, 0, NULL, 0, NULL,
    0, 0, NULL, 0, NULL, NULL, NULL, 0};

    get_history(&all);
    ut_assert((int)all.history.vector[0] == 1);
    ut_assert_str_eq((char *)all.history.vector[2], "ls");
    all.input = command2;
    get_history(&all);
    ut_assert((int)all.history.vector[3] == 2);
    ut_assert_str_eq((char *)all.history.vector[5], "ui");
}

void test_get_comp(void)
{
    char *bin = "test";
    char *args[3] = {"test1", "test2", 0};
    char **res = get_comp(bin, args);
    int count = 0;

    for (int i = 0; res[i]; i++) {
        count += 1;
    }
    ut_assert(count == 3);
    ut_assert_str_eq(res[0], "test");
    ut_assert_str_eq(res[1], "test1");
    ut_assert_str_eq(res[2], "test2");
}

void test_get_bin(void)
{
    char txt[] = "test one";
    int ch = 0;
    char *res = get_bin(txt, &ch);

    ut_assert(ch == 4);
    ut_assert_str_eq(res, "test");
}