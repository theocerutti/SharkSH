/*
** EPITECH PROJECT, 2019
** tree_making
** File description:
** tree_making
*/

#include "exec.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void complete_tree3(tree_t *tree, char *s, tree_t *right, tree_t *left)
{
    int semi = 0;

    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == ';' || s[i] == '>' ||
        (s[i] == '|' && s[i + 1] == '|' && (i == 0 || s[i - 1] != '|')) ||
        (s[i] == '&' && s[i + 1] == '&' && (i == 0 || s[i - 1] != '&')))
            semi = 1;
    for (int i = 0; semi == 0 && s[i] != '\0'; i++) {
        if (s[i] == '|' && s[i + 1] != '|' && s[i - 1] != '|' &&
        is_parenthese(s, i) == 0 && operand_in_quote(s, "|") == 0) {
            get_left_right3(tree, left, right, i);
            break;
        }
    }
}

void complete_tree4(tree_t *tree, char *s, tree_t *right, tree_t *left)
{
    int semi = 0;

    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] == ';' || s[i] == '>')
            semi = 1;
    for (int i = 0; semi == 0 && s[i] != '\0'; i++) {
        if (s[i] == '|' && s[i + 1] == '|' && s[i - 1] != '|' &&
        is_parenthese(s, i) == 0 && operand_in_quote(s, "||") == 0) {
            get_left_right4(tree, left, right, i + 1);
            break;
        }
        if (s[i] == '&' && s[i + 1] == '&' && (i == 0 || s[i - 1] != '&') &&
        is_parenthese(s, i) == 0 && operand_in_quote(s, "&&") == 0) {
            get_left_right5(tree, left, right, i + 1);
            break;
        }
    }
}

void get_left_right(tree_t *tree, tree_t *left, tree_t *right, int i)
{
    if ((left->str = get_left(tree->str, i)) != NULL)
        tree->left = left;
    if ((right->str = get_right(tree->str, i + 1)) != NULL)
        tree->right = right;
    tree->str = NULL;
    tree->str = my_strcpy(";", tree->str);
    if (tree->left != NULL) tree->left->par = 0;
    if (tree->right != NULL) tree->right->par = 0;
    if (tree->par == 1 && tree->left != NULL) tree->left->par = 1;
    if (tree->par == 1 && tree->right != NULL) tree->right->par = 1;
    if (tree->left != NULL)
        complete_tree(left, left->str);
    if (tree->right != NULL)
        complete_tree(right, right->str);
}

void get_commands(char *str, tree_t *tree, tree_t *left, tree_t *right)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ';' && is_parenthese(str, i) == 0 &&
        operand_in_quote(str, ";") == 0) {
            get_left_right(tree, left, right, i);
            break;
        }
    }
    complete_tree2(tree, str, right, left);
    complete_tree4(tree, str, right, left);
    complete_tree3(tree, str, right, left);
    complete_tree5(tree, str, right, left);
}

void complete_tree(tree_t *tree, char *str)
{
    tree_t *right = malloc(sizeof(*right));
    tree_t *left = malloc(sizeof(*left));

    right->par = 0;
    right->next = 0;
    left->next = 0;
    left->par = 0;
    tree->right = NULL;
    tree->left = NULL;
    if (tree->str == NULL) return;
    get_commands(str, tree, left, right);
    if (is_parenthese(str, strlen(str)) == 1) {
        if (split_after_parenthese(tree, str, left, right) == 0) {
            tree->left->par = 1;
            tree->par = 5;
            tree->right->par = 5;
        } else tree->par = 1;
        complete_tree(tree->left, tree->left->str);
        if (tree->right != NULL) complete_tree(tree->right, tree->right->str);
    }
}