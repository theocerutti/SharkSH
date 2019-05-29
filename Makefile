##
## EPITECH PROJECT, 2019
## makefile
## File description:
## makefile
##

NAME =	sharksh
UNITTEST = unity

MAIN = src/main.c

TESTFILES =	./tests/main.c \
			./tests/unit_tests/compare.c \
			./tests/unit_tests/exception.c \
			./tests/unit_tests/unittest.c \
			./tests/unit_tests/ut_utils.c \
			./tests/src/basic_functions.c \

FILES =	src/redirection/send_to_func.c \
		src/beginning/init.c \
		src/beginning/error_parenthesis.c \
		src/beginning/complete_quotes.c \
		src/beginning/process_globings.c \
		src/lib/usefull.c \
		src/lib/usefull2.c \
		src/lib/usefull3.c \
		src/lib/usefull4.c \
		src/lib/usefull5.c \
		src/lib/linked_list_manipulation.c \
		src/lib/arraylist.c \
		src/lib/split.c \
		src/lib/str_word_array.c \
		src/lib/get_names.c \
		src/lib/linked_list.c \
		src/arguments/get_arguments.c \
		src/arguments/get_arguments2.c \
		src/arguments/get_arg_bis.c \
		src/builtins/builtins_tab.c \
		src/builtins/change_dir.c \
		src/builtins/exit_prog.c \
		src/builtins/check_functions.c \
		src/builtins/cd/cd_back.c \
		src/builtins/cd/cd_error.c \
		src/builtins/cd/cd.c \
		src/builtins/cd/cd_utils.c \
		src/builtins/cd/utils/my_realloc.c \
		src/builtins/cd/utils/env/env.c \
		src/builtins/cd/utils/env/unsetenv.c \
		src/builtins/cd/utils/env/setenv.c \
		src/builtins/cd/utils/my_strcmp.c \
		src/builtins/repeat/repeat.c \
		src/builtins/which_where/which_where.c \
		src/builtins/which_where/which_where_utils.c \
		src/builtins/sharksh/print_info_sharksh.c \
		src/builtins/sharksh/print_info_utils.c \
		src/builtins/echo/echo.c \
		src/builtins/echo/echo_get_param.c \
		src/builtins/echo/echo_check_error.c \
		src/builtins/echo/echo_backtick_slash.c \
		src/builtins/shell_env_local/set/set.c \
		src/builtins/shell_env_local/shell_var_utils/getenv_local.c \
		src/builtins/shell_env_local/shell_var_utils/print_shell_var.c \
		src/builtins/shell_env_local/shell_var_utils/shell_var_env.c \
		src/builtins/shell_env_local/unset/unset.c \
		src/env/put_default_env.c \
		src/env/manage_env.c \
		src/env/manage_env2.c \
		src/env/manage_env3.c \
		src/env/change_old_pwd.c \
		src/execute/execute_functions.c \
		src/execute/execute.c \
		src/execute/exec_v2.c \
		src/lists/lists_array.c \
		src/lists/lists_array2.c \
		src/pipes/my_pipe.c \
		src/pipes/error_input.c \
		src/pipes/error_input_2.c \
		src/tree/tree_making.c \
		src/tree/tree_making2.c \
		src/tree/tree_making3.c \
		src/tree/get_parenthese.c \
		src/redirection/fd_set.c \
		src/redirection/redirect_input_double.c \
		src/redirection/tree_parcours.c \
		src/redirection/which_command.c \
		src/error/input_errors.c \
		src/error/input_errors2.c \
		src/execute/choose_exec.c \
		src/lists/modif_env_cd.c \
		vector/method/create.c \
		vector/method/delete.c \
		vector/method/get.c \
		vector/method/push.c \
		src/history/add_cmd.c \
		src/history/add_cmd_utils.c \
		src/history/print_history.c \
		src/history/get_command_arrow.c \
		src/line_edition/paste_command.c \
		src/line_edition/read_cmdline_command1.c \
		src/line_edition/read_cmdline_command2.c \
		src/line_edition/read_cmdline_command3.c \
		src/line_edition/read_cmdline_command4.c \
		src/line_edition/read_cmdline_utils.c \
		src/line_edition/read_cmdline_utils2.c \
		src/line_edition/read_cmdline.c \
		src/line_edition/cmdline_history_command.c \
		src/line_edition/setup_term.c \
		src/redirection/manage_redir.c \
		src/pipes/init_tree.c \
		src/pipes/quotes.c \
		src/pipes/quotes_2.c \
		src/autocomplete/get_autocomp.c \
		src/builtins/aliases.c \
		src/builtins/unalias.c \
		src/builtins/utils_alias.c \
		src/autocomplete/autocomplete.c \
		src/autocomplete/utils.c \
		src/autocomplete/arrow_function.c \
		src/autocomplete/restore_cursor.c \
		src/lib/word_array_alias.c \
		src/history/check_args.c \
		src/history/change_cmd.c \
		src/history/print_clean.c \

SRC = $(MAIN) $(FILES)

TEST = $(TESTFILES) $(FILES)

OBJ =	$(SRC:.c=.o)

OBJTEST = $(TEST:.c=.o)

CC =	gcc

CFLAGS =	-W -Wall -Wextra -g3 -g -I./include -I./tests/unit_tests/include \
-lncurses -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

CTFLAGS =	-W -Wall -Wextra -g3 -g -I./include -I./tests/unit_tests/include \
-lncurses

RM_TRASH=	*.o *~ *.gcno *.gcda libmy.a *.gch *.out *.data

RM =	rm -f

RULE =	all

all :	$(NAME)

$(UNITTEST) : $(OBJTEST)
	gcc $(OBJTEST) -o $(UNITTEST) $(CTFLAGS)

test :	$(UNITTEST)

$(NAME) :	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

clean :
		$(RM) $(RM_TRASH) $(OBJ) $(OBJTEST)

fclean :	clean
			$(RM) $(NAME)
			$(RM) $(UNITTEST)

re :	fclean all
