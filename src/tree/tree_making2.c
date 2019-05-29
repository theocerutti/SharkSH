/*
** EPITECH PROJECT, 2019
** tree_making2
** File description:
** tree_making2
*/

#include "exec.h"

char *get_left(char *str, int idx)
{
    int size = 0;
    char *arg = NULL;

    if (str[idx - 1] == '|' || str[idx - 1] == '&')
        idx--;
    for (int i = 0; i < idx; i++)
        size++;
    arg = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < idx; i++)
        arg[i] = str[i];
    arg[size] = '\0';
    return (arg);
}

char *get_right(char *str, int idx)
{
    int size = 0;
    int index = 0;
    char *arg = NULL;

    while (str[idx] == '>' || str[idx] == '<' || str[idx] == ' ' ||
    str[idx] == ';' || str[idx] == '|' || str[idx] == '&')
        idx++;
    for (int i = idx; str[i] != '\0'; i++)
        size++;
    arg = malloc(sizeof(char) * (size + 1));
    for (int i = idx; str[i] != '\0'; i++) {
        arg[index] = str[i];
        index++;
    }
    arg[size] = '\0';
    return (arg);
}

void complete_redirections2(tree_t *tree, char *str, int i)
{
    if (str[i] == '>' && str[i + 1] != '>') {
        tree->str = NULL;
        tree->str = my_strcpy(">", tree->str);
        return;
    }
    if (str[i] == '>' && str[i + 1] == '>') {
        tree->str = NULL;
        tree->str = my_strcpy(">>", tree->str);
        return;
    }
}

void complete_redirections(tree_t *tree, char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++)
        if (str[i] == '<' || str[i] == '>') break;
    if (str[i] == '<' && str[i + 1] != '<') {
        tree->str = NULL;
        tree->str = my_strcpy("<", tree->str);
        return;
    }
    if (str[i] == '<' && str[i + 1] == '<') {
        tree->str = NULL;
        tree->str = my_strcpy("<<", tree->str);
        return;
    }
    complete_redirections2(tree, str, i);
}

void get_left_right2(tree_t *tree, tree_t *left, tree_t *right, int i)
{
    if ((left->str = get_left(tree->str, i)) != NULL)
        tree->left = left;
    if ((right->str = get_right(tree->str, i + 1)) != NULL)
        tree->right = right;
    if (tree->left != NULL) tree->left->par = 0;
    if (tree->right != NULL) tree->right->par = 0;
    complete_redirections(tree, tree->str);
    if (tree->left != NULL)
        complete_tree(left, left->str);
    if (tree->right != NULL)
        complete_tree(right, right->str);
}