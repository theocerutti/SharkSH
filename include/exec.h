/*
** EPITECH PROJECT, 2019
** exec
** File description:
** exec
*/

#ifndef EXEC_H_
#define EXEC_H_

#include "lib.h"

extern builtin_t builtins[];

/*
** set / unset shell env
*/

void change_pwd_value_list(char *value, char **env);
int save_alias2(all_t *all);

void update_shell_var_local(all_t *all);
list_t init_shell_var(all_t *all);
const char *my_getenv_local(list_t *var_local, char *key);
void unset(all_t *all);
int unset_shell_var(list_t *shell_var_list, char *key);
void set(all_t *all);
void set_shell_var(list_t *shell_var_list, local_t var);
void print_shell_env(all_t *all);

/*
** Echo functions
*/

#define SIMPLE_QUOTE 0
#define DOUBLE_QUOTE 1
#define NO_QUOTE -1

int get_size_var(char *arg, int i);
void change_cmd_auto(all_t *all, cmdline_t *cline);
char *my_getenv(char *key, fenvlist_t *env);
void echo_builtin(all_t *all);
char *get_param_echo(char **args, int have_n_arg);
void print_backslash(char *arg, int *i, int quoted);
int check_error_echo(char *arg, all_t *all);

/*
** Auto complete
*/

void act_for_new_cmd(kkey_t *arrow, all_t *all, cmdline_t *cline);

void prepare_save_cursor(int i, all_t *all, int nb_space);
void restore_cursor_position(all_t *all, cmdline_t *cline);
char *update_cline(all_t *all, cmdline_t *cline);

int up_arrow(all_t *all, cmdline_t *cline);
int down_arrow(all_t *all, cmdline_t *cline);
int left_arrow(all_t *all, cmdline_t *cline);
int right_arrow(all_t *all, cmdline_t *cline);

void print_complete(all_t *all);

char *my_concat(char *str1, char *str2);
int my_strncmp(char *ref, char *test, int len);
char *my_strcpy_auto(char *to_copy);
void get_command_autocomp(all_t *all, cmdline_t *cline);
void autocomplete(all_t *all, cmdline_t *cline);

/*
** Locate functions (where / which)
*/

int is_an_alias(char *arg, int is_where, char **aliases);
int is_a_shell_builtin(char *cmd, int is_where);
void locate_cmd(all_t *all);

/*
** print_info_sharksh
*/

char *get_line_info_in_file(char *file, char *hashkey);
char *get_cpu_info(void);
char *get_mem_info(void);
char *get_user_name(void);
char *get_kernel_info(void);
void print_info_sharksh(all_t *data);

/*
** repeat functions
*/

void repeat(all_t *all);

/*
** history functions
*/

void finalize_cmd(int *i, int *w, char *final_cmd, char *cmd);
void reduce_space(char *cmd);
void print_command_clean(char *cmd);

void exec_command_x(char *stock, all_t *all, int *begin_end);
void exec_same_cmd(char *stock, all_t *all, int *begin_end);
int check_history(all_t *all);

void reduce(char *cmd, int i);
void history(all_t *all);
void get_history(all_t *all);
char *get_history_cmd_up(all_t *all, cmdline_t *cline);
char *get_history_cmd_down(all_t *all, cmdline_t *cline);

/*
** cd builtins functions
*/

void cd_move(char **command, char **env, int *exit_code);
void cd_home(char **env);
void go_on_pos(char **env, int i, int beg);
void change_pwd_env(char *str, char **env);
void cd_error(char **command, int *did, int *exit_code);
void direction_error(char *path, int *exit_code);
int cd_back(char **env, int *exit_code);
void prepa_set_env(char **env, char *oldpwd, int *exit_code);

/*
** Utils for cd
*/

void if_double_quote(char *str);

void prepare_alias(char *cline);
void save_alias(all_t *all);

void change_old_pwd_value(char *value, char **env);

int my_strcmp_cd(char const *str1, char const *str2);
char *concat_space(char *str1, char *str2);
int is_exist(char *str, char **env);
char *concat_env(char *, char *);
int count_word(char *str);
void set_env(char **command, char **env, int *did, int *exit_code);
void print_env(char **env, int *did);
int unset_env(char **command, char **env, int *did, int *exit_code);
int check_set_new(char **command, char **env, int const len, int *exit_code);
char *concat_env_add(char *env, char *str);
void my_realloc(char **env);
char **str_word_array(char *);
int my_str_isnum(char const *str);
int my_str_isalphanum(char const *str);
int my_str_isalpha(char const *str);
char *my_tab_to_str(char **tabb, char *separator);
int my_strlen(char const *str);
int my_str_isnum_neg(char const *str);
void my_putstr(char const *);
char *int_to_str(int, int);
int my_getnbr(char *);
void my_putchar(char);
int my_put_nbr(int);
char *my_strcpy(char *, char *);
int my_strcmp(char *, char *);
char **get_args(char **, char *);
void change_directory(all_t *);
void my_exit(all_t *);
void my_unsetenv(all_t *);
void my_setenv(all_t *);
void my_env(all_t *);
void existent_func(all_t *);
fenvlist_t *get_env(all_t *, char **);
void go_back_dir(all_t *);
int my_strcmp_env(char *, char *);
char *my_strcat_path(char *, char *next);
char *inspect_namedir(char *path, char *dir);
char *get_namedir(char *path, char *dir);
void get_host_name(all_t *);
void check_home_name(all_t *);
void change_value_env(envlist_t *ev, char *, all_t *, int det);
char **get_args_list(char *, int *ch, int *nb, int index);
char *get_arg_list(char *, int, char *dest);
void special_cases(all_t *);
void change_pwd(all_t *, char *aff);
char *my_itoa(int nb);
void change_pwd_value(all_t *, char *aff, envlist_t *actual);
char **path_to_word_array(char **path, char *);
char *pwd_go_back(all_t *);
int change_old_pwd(all_t *, char *aff);
char *get_old_pwd(all_t *);
char **cat_exec_path(char *);
char **get_exec_path(all_t *);
void segfault_errors(int status, all_t *all);
void execute_program(char *path, all_t *, int ppid, int nb);
void set_values(all_t *, envlist_t *actual);
int setenv2(all_t *);
void remove_value(envlist_t *ev, int size);
char *get_new_env(char *, char *add, int);
int not_alphanum(char *);
char **get_array_env(char **);
int init(all_t *, char *, int);
void exec_command(all_t *all);
void init2(all_t *);
char *my_strcpy_real(char *dest, char const *src);
fenvlist_t *envlist_init(void);
void list_insert_first(fenvlist_t *, char *key, char *value);
void list_insert_last(envlist_t *, char *key, char *value);
void list_insert_between(envlist_t *, envlist_t *bef, char *k, char *v);
void list_supress_elem(fenvlist_t *c, envlist_t *e, envlist_t *b,
envlist_t *a);
void execv2(all_t *all, char **env, tree_t *tree, int *fd);
void list_affich(fenvlist_t *, char **env);
void list_to_array(fenvlist_t *list, all_t *);
char **get_comp(char *bin, char **args);
char *get_bin(char *, int *ch);
void with_pipe(all_t *all);
void my_pipe(all_t *all);
int do_builtin_redirect(char *path, char **args, all_t *all, int *fd);
void execute_tree(tree_t *, char **, all_t *all);
void complete_tree(tree_t *, char *);
void affich_not_found(char *);
char *valid_path(char **, all_t *all);
void set_pipe(tree_t *);
void set_semi_colon(tree_t *);
void set_simple_left(tree_t *);
void nothing(tree_t *);
void set_simple_right(tree_t *);
void execute_command(char *path, char **ope, char **, all_t *);
char *get_left(char *, int);
char *get_right(char *, int);
void complete_redirections(tree_t *, char *);
void get_left_right2(tree_t *, tree_t *left, tree_t *right, int i);
void execute_pipe(char *path, char **args, char **, int check);
int next_to_redirection(char *, int);
int error_input2(char *, int nb);
int next_command(char *, int i, int);
int pipe_error(char *, int i);
int error_input(char *str);
void choose_exec(all_t *, char **, tree_t *, int *);
void choose_pipe_exec(tree_t *, char **, all_t *, int);
int my_builtin(all_t *, char *, char **);
int is_builtin(all_t *, char *);
char **my_double_strcpy(char **str, char **dest);
void execute_redirect(char *path, char **args, all_t *all, int *fd);
void execute_redirect_left(tree_t *tree, char **env, all_t *all);
void execute_tree_pipe(tree_t *tree, char **env, all_t *all);
void execute_semi_colon(tree_t *tree, char **env, all_t *all);
char **str_word_array(char *str);
void prepare_exec(tree_t *tree, all_t *all, char **env, int *fd);
void display_input_line(all_t *all);
void print_tab(char **);
char is_in(char c, char *str);
void free_tab(char **);
int error_input_match(char *str);
int operand_in_quote(char *str, char *op);
char *big_strcat(int nb_args, ...);
char **word_array_alias(char const *str);
char *my_strcat(char const *dest, char const *src);
void sort_alphanum(list_t *list);
void quotes(all_t *all);
int is_inhib(int j, char c, char *all);
void my_puterror(char *str);
char modif_slash(char *origine, int *j);
int is_sp(char c);
int error_match_special(char *str);
char **args_in_tab(char *str);
void transform_back_line(all_t *all);
void unalias(all_t *all);
char *manage_back_line(all_t *all, char *str, int idx, int size2);
fenvlist_t *put_default_env(all_t *all);
char **my_copy_args(char **str, char **src);
char ***fill_alias_tab(char *str, char ***alias);
char *get_alias(int *idx, char *str, char *alias, int check);
int error_parenthesis(char *str);

arraylist_t *split(const char *txt, const char *sep);
char **process_globings(char **command);

void exec_redirect_right(all_t *, char **, tree_t *, int *);
void execute_redirect_right(tree_t *tree, char **env, all_t *);
void get_args_tree(tree_t *tree, all_t *all);

void get_left_right5(tree_t *tree, tree_t *left, tree_t *right, int i);
void get_left_right4(tree_t *tree, tree_t *left, tree_t *right, int i);
void get_left_right3(tree_t *tree, tree_t *left, tree_t *right, int i);
void complete_tree2(tree_t *tree, char *str, tree_t *right, tree_t *left);
int is_parenthese(char *str, int idx);
void get_next_command(tree_t *tree, tree_t *right, char *str, int end);
int split_after_parenthese(tree_t *, char *, tree_t *, tree_t *);


char **my_strcpy_tab(char **dest, char **src);
char *my_tab_to_str(char **to_copy, char *separator);
void complete_tree5(tree_t *tree, char *str, tree_t *right, tree_t *left);
int exec_redirection_db(tree_t *tree, all_t *all);

char **manage_alias(char **args, all_t *all);

#endif
