/*
** EPITECH PROJECT, 2019
** tree_making3
** File description:
** tree_making3
*/

#include "exec.h"

int is_parenthese(char *str, int idx)
{
    for (int i = 0; i < idx; i++)
        if (str[i] == '(')
            return (1);
    return (0);
}

void complete_tree2(tree_t *tree, char *str, tree_t *right, tree_t *left)
{
    int semi = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == ';')
            semi = 1;
    for (int i = 0; semi == 0 && str[i] != '\0'; i++) {
        if ((str[i] == '>') && is_parenthese(str, i) == 0) {
            if (operand_in_quote(str, ">") == 0 && str[i] == '>') {
                get_left_right2(tree, left, right, i);
                break;
            }
        }
    }
}

void get_left_right3(tree_t *tree, tree_t *left, tree_t *right, int i)
{
    if ((left->str = get_left(tree->str, i)) != NULL)
        tree->left = left;
    if ((right->str = get_right(tree->str, i + 1)) != NULL)
        tree->right = right;
    tree->str = NULL;
    tree->str = my_strcpy("|", tree->str);
    if (tree->left != NULL) tree->left->par = 0;
    if (tree->right != NULL) tree->right->par = 0;
    if (tree->par == 1 && tree->left != NULL) tree->left->par = 1;
    if (tree->par == 1 && tree->right != NULL) tree->right->par = 1;
    if (tree->left != NULL)
        complete_tree(left, left->str);
    if (tree->right != NULL)
        complete_tree(right, right->str);
}

void get_left_right4(tree_t *tree, tree_t *left, tree_t *right, int i)
{
    if ((left->str = get_left(tree->str, i)) != NULL)
        tree->left = left;
    if ((right->str = get_right(tree->str, i + 1)) != NULL)
        tree->right = right;
    tree->str = NULL;
    tree->str = my_strcpy("||", tree->str);
    if (tree->left != NULL) tree->left->par = 0;
    if (tree->right != NULL) tree->right->par = 0;
    if (tree->par == 1 && tree->left != NULL) tree->left->par = 1;
    if (tree->par == 1 && tree->right != NULL) tree->right->par = 1;
    if (tree->left != NULL)
        complete_tree(left, left->str);
    if (tree->right != NULL)
        complete_tree(right, right->str);
}

void get_left_right5(tree_t *tree, tree_t *left, tree_t *right, int i)
{
    if ((left->str = get_left(tree->str, i)) != NULL)
        tree->left = left;
    if ((right->str = get_right(tree->str, i + 1)) != NULL)
        tree->right = right;
    tree->str = NULL;
    tree->str = my_strcpy("&&", tree->str);
    if (tree->left != NULL) tree->left->par = 0;
    if (tree->right != NULL) tree->right->par = 0;
    if (tree->par == 1 && tree->left != NULL) tree->left->par = 1;
    if (tree->par == 1 && tree->right != NULL) tree->right->par = 1;
    if (tree->left != NULL)
        complete_tree(left, left->str);
    if (tree->right != NULL)
        complete_tree(right, right->str);
}