/*
** EPITECH PROJECT, 2019
** echo
** File description:
** echo
*/

#include "exec.h"

static void check_print_value_shell(list_t *shell_var, char *var)
{
    node_t *tmp = *shell_var;

    while (tmp != NULL) {
        if (!strncmp(tmp->var.key, var, strlen(tmp->var.key))) {
            my_putstr(tmp->var.value);
            break;
        }
        tmp = tmp->next;
    }
}

static void print_var(list_t *shell_var, char *arg, int *i, fenvlist_t *env)
{
    int j = 0;
    char *var = malloc(sizeof(char) * (get_size_var(arg, *i) + 1));
    const char *token = NULL;

    for (; arg[*i] == '$'; *i += 1);
    for (j = 0; !is_in(arg[*i], " $\'\"") && arg[*i] != '\0'; *i += 1)
        if (arg[*i] != '$') {
            var[j] = arg[*i];
            j++;
        }
    var[j] = '\0';
    if ((token = my_getenv(var, env)) == NULL) {
        check_print_value_shell(shell_var, var);
    } else
        my_putstr(token);
    if (arg[*i] == '$')
        *i -= 1;
}

static void check_print_special_var(char *arg, int *i, fenvlist_t *env)
{
    if (arg[*i] == '~' && (is_in(arg[*i + 1], "$ ") || arg[*i + 1] == '\0') &&
    (*i == 0 || (*i > 0 && is_in(arg[*i - 1], "$ ")))) {
        my_putstr(my_getenv("HOME", env));
        *i += 1;
    }
}

static void print_echo_format(list_t *shell_var, char *arg, fenvlist_t *env)
{
    int quoted = NO_QUOTE;
    int len_arg = strlen(arg);

    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '\'')
            quoted = SIMPLE_QUOTE;
        else if (arg[i] == '\"')
            quoted = DOUBLE_QUOTE;
        check_print_special_var(arg, &i, env);
        if (arg[i] == '$' && arg[i + 1] != ' ' &&
        arg[i + 1] != '\0' && quoted != SIMPLE_QUOTE) {
            print_var(shell_var, arg, &i, env);
        } else if (arg[i] == '\\')
            print_backslash(arg, &i, quoted);
        if (i >= len_arg)
            return;
        if (!is_in(arg[i], "\'\""))
            my_putchar(arg[i]);
    }
}

void echo_builtin(all_t *all)
{
    char *arg = NULL;
    int have_n_arg = FALSE;

    if (all->args[1] != NULL && !my_strcmp(all->args[1], "-n"))
        have_n_arg = TRUE;
    arg = get_param_echo(all->args, have_n_arg);
    if (arg == NULL || check_error_echo(arg, all) == ERROR) {
        all->exit_code = 1;
        return;
    }
    if (arg != NULL)
        print_echo_format(&all->shell_var, arg, all->env);
    if (all->args[1] == NULL || my_strcmp(all->args[1], "-n"))
        my_putchar('\n');
    all->exit_code = 0;
}