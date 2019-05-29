/*
** EPITECH PROJECT, 2019
** send_to_func
** File description:
** send to function
*/

#include "exec.h"

void with_pipe(all_t *all)
{
    my_pipe(all);
}

int operand_in_quote(char *str, char *op)
{
    int quote = -1;
    int double_quote = -1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'')
            quote *= -1;
        if (str[i] == '\"')
            double_quote *= -1;
        if (str[i] == op[0] && (op[1] == '\0' || (str[i + 1] != '\0' \
        && str[i + 1] == op[1]))) {
            if (quote == 1 || double_quote == 1)
                return (1);
            else
                return (0);
        }
    }
    return (2);
}

void complete_tree5(tree_t *tree, char *str, tree_t *right, tree_t *left)
{
    int semi = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ';' || str[i] == '>' || str[i] == '|' || str[i] == '&')
            semi = 1;
    for (int i = 0; semi == 0 && str[i] != '\0'; i++) {
        if ((str[i] == '<') && is_parenthese(str, i) == 0) {
            if (operand_in_quote(str, "<") == 0 && str[i] == '<') {
                get_left_right2(tree, left, right, i);
                break;
            }
        }
    }
}