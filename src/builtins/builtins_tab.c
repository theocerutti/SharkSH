/*
** EPITECH PROJECT, 2019
** init
** File description:
** init
*/

#include "exec.h"

builtin_t builtins[] =
{
    {"cd", &change_directory},
    {"exit", &my_exit},
    {"unsetenv", &my_unsetenv},
    {"setenv", &my_setenv},
    {"env", &my_env},
    {"printenv", &my_env},
    {"other", &existent_func},
    {"sharksh", &print_info_sharksh},
    {"history", &history},
    {"repeat", &repeat},
    {"which", &locate_cmd},
    {"where", &locate_cmd},
    {"alias", &save_alias},
    {"unalias", &unalias},
    {"echo", &echo_builtin},
    {"set", &set},
    {"@", &print_shell_env},
    {"unset", &unset},
    {NULL, NULL}
};