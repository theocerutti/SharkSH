/*
** EPITECH PROJECT, 2019
** repeat
** File description:
** repeat
*/

#include "exec.h"

static char *search_cmd(char *cmd, char *path)
{
    char *exec_path = NULL;

    exec_path = my_strcat_path(path, cmd);
    if (!access(exec_path, F_OK)) {
        return (exec_path);
    }
    free(exec_path);
    return (NULL);
}

static int check_error_locate_cmd(char **args)
{
    int len_args = 0;

    for (len_args = 0; args[len_args] != NULL; len_args++);
    if (len_args < 2) {
        printf("%s: Too few arguments.\n", args[0]);
        return (ERROR);
    }
    return (SUCCESS);
}

static void handle_locate(char **path, all_t *all, int i, int is_where)
{
    char *exec_path = NULL;
    int cmd = 0;

    for (int j = 0; path[j] != NULL && cmd == 0; j++) {
        exec_path = search_cmd(all->args[i], path[j]);
        if (exec_path) {
            if (!is_where)
                cmd++;
            printf("%s\n", exec_path);
        }
    }
    if (!is_where && cmd == 0) {
        printf("%s: Command not found.\n", all->args[i]);
        all->exit_code = 1;
    }
}

static char **get_tab_alias(char *alias)
{
    char **aliases = NULL;

    if (alias[0] != '\0')
        aliases = word_array_alias(alias);
    return (aliases);
}

void locate_cmd(all_t *all)
{
    char **path = get_exec_path(all);
    int is_builtin = FALSE;
    int is_alias = FALSE;
    int is_where = !strncmp(all->args[0], "where", strlen(all->args[0]));
    char **aliases = get_tab_alias(all->alias);

    quotes(all);
    if (check_error_locate_cmd(all->args) == ERROR) {
        all->exit_code = 1;
        return;
    }
    for (int i = 1; all->args[i] != NULL; i++, is_builtin = FALSE) {
        if (!strncmp(all->args[i], "-", strlen(all->args[i])))
            all->exit_code = 1;
        is_builtin = is_a_shell_builtin(all->args[i], is_where);
        if (all->alias[0] != '\0')
            is_alias = is_an_alias(all->args[i], is_where, aliases);
        if ((!is_builtin && !is_alias && !is_where) || is_where)
            handle_locate(path, all, i, is_where);
    }
}