/*
** EPITECH PROJECT, 2019
** echo_check_error
** File description:
** echo_check_error
*/

#include "exec.h"

static int have_illegal_var_name(char *arg)
{
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '$' && is_in(arg[i + 1], "&~\"\'{([-|\\_^)]+=}")) {
            fprintf(stderr, "Illegal variable name.\n");
            return (TRUE);
        }
    }
    return (FALSE);
}

static int check_undefined_var(all_t *all, char *token)
{
    node_t *tmp = all->shell_var;

    while (tmp != NULL) {
        if (!strncmp(tmp->var.key, token, strlen(tmp->var.key)))
            return (TRUE);
        tmp = tmp->next;
    }
    fprintf(stderr, "%s: Undefined variable.\n", token);
    return (FALSE);
}

static int is_known_variable(char *arg, int i, all_t *all)
{
    char *token = NULL;
    const char *env_var = NULL;
    int j = 0;
    int size_tok = 0;

    for (; arg[i] == '$'; i++);
    for (int z = i; !is_in(arg[z], " $\'\"") && arg[z] != '\0';
    z++, size_tok++)
        size_tok++;
    token = malloc(sizeof(char) * (size_tok + 1));
    for (j = 0; !is_in(arg[i], " $\'\"") && arg[i] != '\0'; i++, j++)
        token[j] = arg[i];
    token[j] = '\0';
    if ((env_var = my_getenv(token, all->env)) == NULL)
        return (check_undefined_var(all, token));
    return (TRUE);
}

static int check_home(char *arg, all_t *all, int *i)
{
    if (arg[*i] == '~' && (is_in(arg[*i + 1], "$ ") || arg[*i + 1] == '\0') &&
    (*i == 0 || (*i > 0 && is_in(arg[*i - 1], "$ ")))) {
        if (my_getenv("HOME", all->env) == NULL) {
            fprintf(stderr, "No $home variable set.\n");
            return (ERROR);
        }
        *i += 1;
    }
    return (SUCCESS);
}

int check_error_echo(char *arg, all_t *all)
{
    int len = strlen(arg);

    if (have_illegal_var_name(arg) == TRUE)
        return (ERROR);
    for (int i = 0; i < len; i++) {
        if (check_home(arg, all, &i) == ERROR)
            return (ERROR);
        if (arg[i] == '$' && arg[i + 1] != '\0' && arg[i + 1] != ' ') {
            i++;
            if (is_known_variable(arg, i, all) == FALSE)
                return (ERROR);
        }
    }
    return (SUCCESS);
}