CFLAGS = -Wall -Wextra -Werror


SRC = ft_lstadd_back.c ft_lstnew.c ft_split.c ft_strdup.c ft_strjoin_with.c ft_strlcpy.c ft_strlen.c \
	  ft_substr.c minishell.c parsing.c syntax_errors.c env_utils.c ft_strcmp.c init_env.c ft_strcmp_exp.c \
	  parsing_utils_1.c parsing_utils_2.c quote_and_word_tokenization_functions.c pipes_and_redirections_tokenization_functions.c \
	  removing_quote_marks_functions.c expansion_inner_functions.c tokenization.c execution.c check_command.c \
	  sys_error.c env_to_array.c setup_pipe.c print_error_1.c handle_redirections.c ft_putstr_fd.c execute_builtin.c \
	  built-in_cd.c built-in_echo.c built-in_env.c built-in_exit.c built-in_export.c built-in_pwd.c built-in_unset.c \
	  ft_isdigit.c ft_isalnum.c ft_isalpha.c free_split.c env_sort.c export_utils.c restore_stdio.c ft_atoi.c \
	  ft_itoa.c print_error_2.c set_signal.c heredoc_expand_line.c ft_strjoin.c disable_echoctl.c ft_memcpy.c
all :
	cc  $(SRC) -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib -I/goinfre/$(USER)/homebrew/opt/readline/include
