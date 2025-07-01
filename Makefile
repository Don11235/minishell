CFLAGS = -Wall -Wextra -Werror


SRC =	check_command.c execution.c ft_lstadd_back.c ft_lstnew.c ft_split.c ft_strdup.c \
		ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_substr.c minishell.c parsing.c syntax_errors.c
all :
	cc  $(SRC) -lreadline