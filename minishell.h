/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:41:42 by ytlidi            #+#    #+#             */
/*   Updated: 2025/06/13 14:32:24 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_tokens
{
	TOKEN_WORD,
	TOKEN_S_QUOTE,
	TOKEN_D_QUOTE,
	TOKEN_PIPE,
	TOKEN_RD_IN,
	TOKEN_RD_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_tokens;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	int						type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				*command;
	char				**args;
	t_redirection		*rds;
	int					pipe_in;
	int					pipe_out;   //      ls    ->      test      ->     |      -> .......
	struct s_command	*next;
	// struct s_command	*prev;
}	t_command;

t_token			*ft_lstnew_token(char *token);
t_command		*ft_lstnew_command(char **args);
t_redirection	*ft_lstnew_redirection(int type, char *file);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstadd_back_command(t_command **lst, t_command *new);
void			ft_lstadd_back_redirection(t_redirection **lst, t_redirection *new);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(char *src);
t_token			*parse_input(char *str);
size_t			ft_strlen(const char *s);

