/*
** EPITECH PROJECT, 2019
** struct
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include "exec.h"

typedef struct envlist
{
    char *key;
    char *value;
    struct envlist *next;
} envlist_t;

typedef struct fenvlist
{
    envlist_t *first;
} fenvlist_t;

typedef struct arglist
{
    char *bin;
    char **args;
    char **all;
    int nb;
    struct arglist *next;
} arglist_t;

typedef struct farglist
{
    arglist_t *first;
} farglist_t;

typedef struct tree
{
    int par;
    int fd[2];
    char *str;
    char **args;
    char *path;
    int success;
    char next;
    struct tree *right;
    struct tree *left;
} tree_t;

typedef struct all
{
    char **av;
    int ac;
    int exit_code;
    char *input;
    char **args;
    int ex;
    int ppid;
    int success;
    int *fd;
    fenvlist_t *env;
    farglist_t *arg;
    char *current;
    char *pwd;
    char **ev_exec;
    my_vector_t history;
    my_vector_t complete;
    int left_decal;
    int up_decal;
    int str_on;
    int index_comp;
    int len_bin;
    int par;
    int fd_parenth;
    char *file;
    int fd_file;
    int *fd_exec;
    int set_in;
    int *fd_double;
    int set_out;
    int is_pipe;
    list_t shell_var;
    int is_builtin;
    char *last_command;
    char *par_file;
    char *alias;
    int fd_redir;
} all_t;

typedef struct builtin_s
{
    char *name;
    void (*exec)(all_t *);
} builtin_t;

typedef struct fd_set_s
{
    char *function;
    void (*ptr)(tree_t *);
} fd_set_t;

typedef struct sys_info_s {
    char *flag;
    char *info;
} sys_info_t;

#endif /* !STRUCT_H_ */
