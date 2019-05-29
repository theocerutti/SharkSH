/*
** EPITECH PROJECT, 2019
** linked_list header
** File description:
** header
*/

typedef struct shell_var_s {
    char *key;
    char *value;
    int parenthesis;
} local_t;

typedef struct node_t {
    local_t var;
    struct node_t *next;
} node_t;
typedef node_t *list_t;

void delete_list(list_t *list);
void push(list_t *list, local_t new_var);
void push_index(list_t *list, local_t new_var, int n);
void pop_index(list_t *list, int n);
void print_list(list_t *list);
int is_empty(list_t list);