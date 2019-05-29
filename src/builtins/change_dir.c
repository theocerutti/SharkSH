/*
** EPITECH PROJECT, 2019
** change_dir
** File description:
** change dir
*/

#include "exec.h"

void change_directory(all_t *a)
{
    char *oldpwd = NULL;
    char **command = NULL;
    int did = 0;
    int exist = is_exist("OLDPWD", a->ev_exec);

    oldpwd = getcwd(oldpwd, 0);
    command = str_word_array(a->input);
    if (my_strcmp_cd("cd", command[0]) == 1 && count_word(a->input) == 2) {
        cd_move(command, a->ev_exec, &a->exit_code);
        did = 1;
    } else if (my_strcmp_cd("cd", command[0]) == 1 && \
    count_word(a->input) == 1) {
        cd_home(a->ev_exec);
        did = 1;
    } else
        cd_error(command, &did, &a->exit_code);
    if (exist != -1)
        a->ev_exec[exist] = concat_env("OLDPWD", oldpwd);
    else
        prepa_set_env(a->ev_exec, oldpwd, &a->exit_code);
}