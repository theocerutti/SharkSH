/*
** EPITECH PROJECT, 2019
** get_paranthese
** File description:
** manage parethese
*/

#include "exec.h"

int get_next_command2(tree_t *tree, int i, char *str)
{
    if (str[i] == '<') {
        if (str[i + 1] == '<')
            tree->str = my_strcpy("<<", tree->str);
        else
            tree->str = my_strcpy("<", tree->str);
        return (1);
    }
    if (str[i] == '>') {
        if (str[i + 1] == '>')
            tree->str = my_strcpy(">>", tree->str);
        else
            tree->str = my_strcpy(">", tree->str);
        return (1);
    }
    if (str[i] == '&' && str[i + 1] == '&') {
        tree->str = my_strcpy("&&", tree->str);
        return (1);
    }
    return (0);
}

void get_next_command(tree_t *tree, tree_t *right, char *str, int end)
{
    tree->str = NULL;
    for (int i = end; str[i] != '\0'; i++) {
        if (str[i] == ';') {
            tree->str = my_strcpy(";", tree->str);
            break;
        }
        if (str[i] == '|' && str[i + 1] == '|') {
            tree->str = my_strcpy("||", tree->str);
            break;
        }
        if (str[i] == '|' && str[i + 1] != '|') {
            tree->str = my_strcpy("|", tree->str);
            break;
        }
        if (get_next_command2(tree, i, str) == 1)
            break;
    }
    if (tree->str != NULL)
        right->str = get_right(str, end + strlen(tree->str));
}

void config_parenthese(char *str, tree_t *tree, tree_t *left, tree_t *right)
{
    int deb = 0;
    int end = 0;
    char *par = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') deb = i;
        if (str[i] == ')') {
            end = i;
            break;
        }
    }
    if (deb >= end) exit(0);
    par = malloc(sizeof(char) * (end - deb));
    for (int i = deb + 1, j = 0; i < end; i++, j++)
        par[j] = str[i];
    par[end - deb - 1] = '\0';
    left->str = my_strcpy(par, left->str);
    tree->left = left;
    get_next_command(tree, right, str, end);
    tree->right = right;
}

int split_after_parenthese(tree_t *t, char *str, tree_t *left, tree_t *right)
{
    config_parenthese(str, t, left, right);
    if (t->str == NULL) {
        t->str = my_strcpy(t->left->str, t->str);
        t->left = NULL;
        t->right = NULL;
        t->next = 0;
        complete_tree(t, t->str);
        return (1);
    }
    t->next = 0;
    if (t->str[0] == ';' || t->str[0] == '&' ||
    (t->str[0] == '|' && t->str[1] == '|'))
        t->left->next = 0;
    else if (t->str[0] == '|')
        t->left->next = 1;
    else
        t->left->next = 2;
    return (0);
}