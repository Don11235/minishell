CFLAGS = -Wall -Wextra -Werror


SRC =	ft_lstadd_back.c ft_lstnew.c ft_split.c ft_strdup.c \
		ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_substr.c minishell.c parsing.c syntax_errors.c \
		env_utils.c ft_lstadd_back_execution.c ft_lstnew_execution.c ft_strcmp.c init_env.c \
		ft_strcmp_exp.c parsing_utils.c
all :
	cc  $(SRC) -lreadline