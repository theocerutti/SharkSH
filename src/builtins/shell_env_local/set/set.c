/*
** EPITECH PROJECT, 2019
** set
** File description:
** set
*/

#include "exec.h"

static int check_error_args_set(char **args)
{
    char *var = NULL;

    for (int i = 1; args[i] != NULL; i++) {
        var = malloc(sizeof(char) * strlen(args[i]));
        for (int j = 0; args[i][j] != '\0' && args[i][j] != '='; j++)
            var[j] = args[i][j];
        if (!LETTER(args[i][0])) {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return (ERROR);
        }
        if (!my_str_isalphanum(args[i]) && !is_in('=', args[i])) {
            fprintf(stderr,
            "set: Variable name must contain alphanumeric characters.\n");
            return (ERROR);
        }
        free(var);
    }
    return (SUCCESS);
}

static void alloc_key_value(char **key, char **value, char *arg)
{
    int j = 0;
    int z = 0;

    for (j = 0; arg[j] != '\0' && arg[j] != '='; j++);
    *key = malloc(sizeof(char) * (j + 1));
    if (arg[j] == '=')
        j++;
    for (z = 0; arg[j] != '\0'; j++, z++);
    *value = malloc(sizeof(char) * (z + 1));
}

static void set_all_var(list_t *shell_var_list, char **args)
{
    int j = 0;
    int z = 0;
    char *key = NULL;
    char *value = NULL;

    for (int i = 1; args[i] != NULL; i++) {
        alloc_key_value(&key, &value, args[i]);
        for (j = 0; args[i][j] != '\0' && args[i][j] != '='; j++)
            key[j] = args[i][j];
        key[j] = '\0';
        if (args[i][j] == '=')
            j++;
        for (z = 0; args[i][j] != '\0'; j++, z++)
            value[z] = args[i][j];
        value[z] = '\0';
        set_shell_var(shell_var_list, (local_t){key, value, 0});
    }
}

void set_shell_var(list_t *shell_var_list, local_t var)
{
    node_t *tmp = *shell_var_list;

    while (tmp != NULL) {
        if (!strcmp(tmp->var.key, var.key)) {
            tmp->var.value = var.value;
            break;
        }
        tmp = tmp->next;
    }
    if (!tmp) {
        push(shell_var_list, var);
        sort_alphanum(shell_var_list);
    }
}

void set(all_t *all)
{
    if (all->args[1] == NULL) {
        print_shell_env(all);
        return;
    }
    if (check_error_args_set(all->args) == ERROR) {
        all->exit_code = 1;
        return;
    }
    set_all_var(&all->shell_var, all->args);
}