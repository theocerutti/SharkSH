/*
** EPITECH PROJECT, 2019
** shell_var_env
** File description:
** shell_var_env
*/

#include "exec.h"

void update_shell_var_local(all_t *all)
{
    list_t *vars_l = &all->shell_var;

    set_shell_var(vars_l, (local_t){"?", my_itoa(all->exit_code), 0});
    set_shell_var(vars_l, (local_t){"status", my_itoa(all->exit_code), 0});
    set_shell_var(vars_l, (local_t){"cwd", all->pwd, 0});
    set_shell_var(vars_l, (local_t){"dirstack", all->pwd, 0});
    set_shell_var(vars_l, (local_t){"path", my_getenv("PATH", all->env), 0});
    set_shell_var(vars_l, (local_t){"term", my_getenv("TERM", all->env), 0});
    all->last_command = (char *)all->history.vector[all->history.size - 1];
}

void init_shell_var3(list_t *shell_var)
{
    push(shell_var, (local_t){"version", "version Sharksh 0.1", 0});
    push(shell_var, (local_t){"killring", "30", 0});
    push(shell_var, (local_t){"owd", "", 0});
    push(shell_var, (local_t){"autolist", "", 0});
    push(shell_var, (local_t){"cdtohome", "", 0});
    push(shell_var, (local_t){"history", "100", 0});
    push(shell_var, (local_t){"csubstnonl", "", 0});
    push(shell_var, (local_t){"autoexpand", "", 0});
    push(shell_var, (local_t){"echo_style", "both", 0});
    push(shell_var, (local_t){"edit", "", 0});
}

void init_shell_var2(all_t *all, list_t *shell_var)
{
    struct group *grp = NULL;
    struct passwd *pw = NULL;
    uid_t uid;
    uid = geteuid();
    pw = getpwuid(uid);
    grp = getgrgid(pw->pw_gid);

    push(shell_var, (local_t){"euid", my_itoa(geteuid()), 0});
    push(shell_var, (local_t){"euser", pw->pw_name, 0});
    push(shell_var, (local_t){"gid", my_itoa(pw->pw_gid), 0});
    push(shell_var, (local_t){"group", grp->gr_name, 0});
    push(shell_var, (local_t){"?", my_itoa(all->exit_code), 0});
    push(shell_var, (local_t){"status", my_itoa(all->exit_code), 0});
    push(shell_var, (local_t){"*", my_tab_to_str(all->av, " "), 0});
    push(shell_var, (local_t){"#", my_itoa(all->ac), 0});
    push(shell_var, (local_t){"$", my_itoa(getpid()), 0});
    push(shell_var, (local_t){"uid", my_itoa(pw->pw_uid), 0});
    push(shell_var, (local_t){"user", pw->pw_name, 0});
    push(shell_var, (local_t){"home", pw->pw_dir, 0});
}

list_t init_shell_var(all_t *all)
{
    list_t shell_var = NULL;

    push(&shell_var, (local_t){"argv", "", 1});
    push(&shell_var, (local_t){"prompt", "%U%m%u:%B%~%b%#", 0});
    push(&shell_var, (local_t){"prompt2", "%R?", 0});
    push(&shell_var, (local_t){"prompt3", "CORRECT>%R (y|n|e|a)?", 0});
    push(&shell_var, (local_t){"shell", "sharksh", 0});
    push(&shell_var, (local_t){"shlvl", my_getenv("SHLVL", all->env), 0});
    push(&shell_var, (local_t){"sharksh", "0.1", 0});
    push(&shell_var, (local_t){"tty", "pts/1", 0});
    push(&shell_var, (local_t){"term", my_getenv("TERM", all->env), 0});
    push(&shell_var, (local_t){"addsuffix", "", 0});
    push(&shell_var, (local_t){"anyerror", "", 0});
    push(&shell_var, (local_t){"cwd", getcwd(NULL, 0), 0});
    push(&shell_var, (local_t){"dirstack", getcwd(NULL, 0), 0});
    push(&shell_var, (local_t){"path", my_getenv("PATH", all->env), 1});
    init_shell_var2(all, &shell_var);
    init_shell_var3(&shell_var);
    sort_alphanum(&shell_var);
    return (shell_var);
}