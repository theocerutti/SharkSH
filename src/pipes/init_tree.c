/*
** EPITECH PROJECT, 2019
** init_tree
** File description:
** init_tree
*/

#include "exec.h"

int operand(char op, char *str)
{
    if (op == '|' && operand_in_quote(str, "|") == 0)
        return (0);
    if (op == '&' && operand_in_quote(str, "&") == 0)
        return (0);
    if (op == '>' && operand_in_quote(str, ">") == 0)
        return (0);
    if (op == '<' && operand_in_quote(str, "<") == 0)
        return (0);
    if (op == ';' && operand_in_quote(str, ";") == 0)
        return (0);
    return (1);
}

void get_args_tree2(tree_t *tree, all_t *all, int check)
{
    for (int i = 0; tree->str[i] != '\0'; i++)
        if ((tree->str[i] == '|' || tree->str[i] == ';' ||
        tree->str[i] == '<' || tree->str[i] == '>' ||
        tree->str[i] == '&') && operand(tree->str[i], tree->str) == 0)
            check = 1;
    if (check == 0) {
        tree->args = args_in_tab(tree->str);
        if (tree->args != NULL && is_builtin(all, tree->args[0]) == 1)
            quotes(all);
        if (tree->args != NULL) tree->args = process_globings(tree->args);
        if (tree->args != NULL) tree->args = manage_alias(tree->args, all);
        if (tree->args != NULL) tree->path = valid_path(tree->args, all);
        else tree->path = NULL;
    }
    if (tree->left != NULL)
        get_args_tree(tree->left, all);
    if (tree->right != NULL)
        get_args_tree(tree->right, all);
}

void get_args_tree(tree_t *tree, all_t *all)
{
    int check = 0;

    if (tree->str == NULL || tree->str[0] == '\0') {
        tree = NULL;
        return;
    }
    tree->success = 0;
    if (tree->par == 1) {
        if (tree->right != NULL)
            tree->right->par = 1;
        if (tree->left != NULL)
            tree->left->par = 1;
    }
    get_args_tree2(tree, all, check);
}