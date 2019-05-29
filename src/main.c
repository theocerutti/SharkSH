/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "exec.h"
#include <signal.h>

void my_sigsegv(int sig)
{
    (void)sig;
    exit(0);
}

void init_all(all_t *all, char **env)
{
    if (env[0] != NULL) {
        all->ev_exec = get_array_env(env);
        all->env = get_env(all, env);
    } else
        all->env = put_default_env(all);
    all->fd_redir = 0;
    all->current = getcwd(all->current, 0);
    all->pwd = getcwd(all->pwd, 0);
    all->current = getenv("HOME");
    all->history = vector_create(15);
    all->complete = vector_create(100);
    all->shell_var = init_shell_var(all);
    all->par_file = my_strcpy("./src/builtins/cd/utils/env/.parenthese",
    all->par_file);
    fd_out = 1;
}

int main(int ac, char **av, char **env)
{
    all_t all = {.av = av, .ac = ac, .env = NULL, .input = NULL,
    .current = NULL, .ev_exec = NULL, .alias = "\0", .exit_code = 0};

    (void)ac;
    (void)av;
    signal(SIGSEGV, &my_sigsegv);
    init_all(&all, env);
    while (1) {
        init(&all, NULL, 0);
        update_shell_var_local(&all);
        if (!isatty(0) && all.exit_code != 0)
            break;
    }
    return (all.exit_code);
}