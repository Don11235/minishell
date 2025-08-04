CFLAGS = -Wall -Wextra -Werror -I/goinfre/$(USER)/homebrew/opt/readline/include

LDFLAGS = -L/goinfre/$(USER)/homebrew/opt/readline/lib

NAME = minishell


SRC = ft_lstadd_back.c ft_lstnew.c ft_split.c utils_1.c utils_2.c utils_3.c utils_4.c minishell.c \
      parsing.c syntax_errors.c env_utils.c init_env.c parsing_utils_1.c parsing_utils_2.c quote_and_word_tokenization_functions.c \
	  pipes_and_redirections_tokenization_functions.c removing_quote_marks_functions.c expansion_inner_functions.c tokenization.c \
	  resplitting.c removing_quote.c execution.c check_command.c sys_error.c env_to_array.c setup_pipe.c print_error_1.c \
	  handle_redirections.c execute_builtin.c built-in_cd.c built-in_echo.c built-in_env.c built-in_exit.c \
	  built-in_export.c built-in_pwd.c built-in_unset.c free_split.c env_sort.c export_utils.c restore_stdio.c \
	  ft_itoa.c print_error_2.c set_signal.c heredoc_expand_line.c disable_echoctl.c free_list.c free_cmd_list.c free_env.c \
	  ft_split_whitespace.c free_hd_parts.c wait_for_child.c prepare_heredocs.c reset_all_heredoc_fds.c reset_heredoc_fd.c \
	  handle_pipe_fds.c exec_helpers.c heredoc_expand_line_helpers.c
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME) -lreadline

%.o: %.c minishell.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re
